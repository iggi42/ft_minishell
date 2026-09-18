# `mstest m` on branch `claus` — STD_ERR failures, validated

Run on branch **claus** at `1bc803c`; the last commit that touched C sources is `3f28229` (the fix
commit), everything after it is README and docs, and `make -q` confirms the tested binary is current.
Fast variant without valgrind as requested — leaks were already confirmed clean on every case by the
earlier `mstest vm` run.

```
TOTAL TEST COUNT: 941   TESTS PASSED: 841   LEAKING: 0
STD_OUT: 78   STD_ERR: 24   EXIT_CODE: 20
```

**24 cases fail the STD_ERR column.** All 24 are below.

## What the STD_ERR column actually checks

Worth knowing before reading the list — the tester never compares the *text* of the error:

```bash
if [[ -s tmp_err_minishell && ! -s tmp_err_bash ]] || [[ ! -s tmp_err_minishell && -s tmp_err_bash ]]
```

It only asks *"did exactly one of the two shells write something to stderr?"*. So a case fails only
when one shell complains and the other stays quiet, and a case **passes** even when both messages
are completely different. A pass in this column is not proof that the message is right.

## How each case was validated

Same method as `todo/test_out.md`: every case re-run individually with the tester's own `enable -n .`
prefix for bash, capturing both streams; then re-run **in an empty directory** to expose
contamination from the junk files the tester leaves in the project root; then re-run against a
**`master` build** (commit `bdd8175`, built in a throwaway worktree) to separate pre-existing
behaviour from anything my two commits changed.

Direction matters here, so each case is labelled *minishell talks / bash silent* or the reverse.

## Verdict summary

| # | Group | Cases | Direction | Verdict |
|---|---|---|---|---|
| 1 | builtins shadowed by the PATH binary | 6 | ms talks | **real bug**, pre-existing |
| 2 | `2>` fd-prefixed redirection | 3 | ms talks | not in the subject |
| 3 | `~` not expanded | 3 | ms talks | not implemented |
| 4 | no word splitting after expansion | 2 | ms talks | not in the subject |
| 5 | `cd --` | 1 | ms talks | cosmetic, pre-existing |
| 6 | junk files left by the tester | 5 | ms talks (during the run) | **false positive** — same root cause as group 1 |
| 7 | bash complains, minishell stays quiet | 2 | bash talks | `;` and option parsing, out of scope |
| 8 | the two known branch regressions | 2 | ms talks | already logged in `todo/test_out.md` |

**24 total.** 22 of them are "minishell talks, bash is silent"; only 2 are the other way round.

---

## 1. Builtins are shadowed by the binary on PATH — 6 cases — REAL BUG

The most interesting finding in this column, and it is not about error messages at all.

`ms_exec_do_cmd` (in `src/ms_exec_child.c`) looks the command up on PATH **first** and only falls
back to the builtin table if nothing was found:

```c
	path = ms_find_exec_file(argv[0]);
	if (path)
		ms_execve(path, argv);
	bilt = ms_builtin_get(argv[0]);
```

So for every forking builtin — `echo`, `pwd`, `env` — the coreutils binary wins, and minishell's own
implementation never runs. Proof:

```
minishell $> pwd --version          bash $> pwd --version
pwd (GNU coreutils) 8.32            bash: pwd: --: invalid option
minishell $> echo --version         bash $> echo --version
echo (GNU coreutils) 8.32           --version
```

Bash always prefers its builtins over PATH. That is what these six cases see: `pwd test42` runs
`/bin/pwd`, which prints `pwd: ignoring non-option arguments` on stderr, while bash's builtin
silently ignores the argument.

Same behaviour on `master`, so this predates my commits. It also means the `echo` and `pwd` builtins
in this project are effectively dead code on any normal machine — which is worth more than the six
test cases, since the subject asks for them to be implemented.

| case | input | minishell stderr | bash stderr |
|---|---|---|---|
| `1_builtins.sh:367` | `pwd test42\n` | pwd: ignoring non-option arguments\n | *(silent)* |
| `1_builtins.sh:369` | `pwd 42 42 42\n` | pwd: ignoring non-option arguments\n | *(silent)* |
| `1_builtins.sh:371` | `pwd pwd\n` | pwd: ignoring non-option arguments\n | *(silent)* |
| `1_builtins.sh:373` | `pwd pwd pwd\n` | pwd: ignoring non-option arguments\n | *(silent)* |
| `2_correction.sh:254` | `pwd pwd\n` | pwd: ignoring non-option arguments\n | *(silent)* |
| `2_correction.sh:256` | `pwd hello\n` | pwd: ignoring non-option arguments\n | *(silent)* |

## 2. `2>` fd-prefixed redirection — 3 cases — not in the subject

The tokenizer has no notion of a leading file descriptor, so in `cd "wtf" 2>/dev/null` the `2`
becomes a third argument and `cd` complains *"too many arguments"* — on a stderr that was never
redirected. Bash redirects its own message into `/dev/null` and stays silent.

Two separate effects stack here: the wrong message (because of the stray `2`), and the message
being visible at all. The mandatory subject only requires `<`, `>`, `<<` and `>>`.

| case | input | minishell stderr | bash stderr |
|---|---|---|---|
| `1_builtins.sh:233` | `cd '/////' 2>/dev/null\n` | minishell: cd: too many arguments\n | *(silent)* |
| `1_builtins.sh:239` | `cd "doesntexist" 2>/dev/null \n` | minishell: cd: too many arguments\n | *(silent)* |
| `1_builtins.sh:243` | `cd "wtf" 2>/dev/null \n` | minishell: cd: too many arguments\n | *(silent)* |

## 3. `~` is not expanded — 3 cases — not implemented

`cd ~` becomes `chdir("~")`, which fails. Bash expands `~` to `$HOME` and says nothing. Tilde
expansion is not part of the mandatory subject, and these same cases already fail in the STD_OUT
column (`pwd` afterwards prints the wrong directory).

| case | input | minishell stderr | bash stderr |
|---|---|---|---|
| `1_builtins.sh:328` | `pwd\ncd ~\ncd -\npwd\n` | minishell: cd: ~: No such file or directory\n | *(silent)* |
| `1_builtins.sh:337` | `pwd\ncd ~\npwd\n` | minishell: cd: ~: No such file or directory\n | *(silent)* |
| `2_path_check.sh:30` | `cd ~\n` | minishell: cd: ~: No such file or directory\n | *(silent)* |

## 4. No word splitting after expansion — 2 cases — not in the subject

`export tmp_test="/bin/echo 42"` then `$tmp_test` becomes a single argv[0] literally called
`/bin/echo 42`, so minishell reports it as missing; bash splits the value and runs `/bin/echo` with
`42`. Same root cause as the word-splitting group in `todo/test_out.md`.

| case | input | minishell stderr | bash stderr |
|---|---|---|---|
| `10_parsing_hell.sh:216` | `export T="echo segfault \| grep segfault"\n$T\n` | echo segfault \| grep segfault: command not found\n | *(silent)* |
| `1_variables.sh:120` | `export tmp_test="/bin/echo 42"\n$tmp_test\n$tmp_…` | /bin/echo 42: No such file or directory\n/bin/echo 42: No such file or… | *(silent)* |

## 5. `cd --` — 1 case — cosmetic

Bash treats `--` as "end of options" and goes to `$HOME` without a word. Minishell tries
`chdir("--")` and reports the failure.

| case | input | minishell stderr | bash stderr |
|---|---|---|---|
| `10_parsing_hell.sh:321` | `cd --\n` | minishell: cd: --: No such file or directory\n | *(silent)* |

## 6. Junk files left by the tester — 5 cases — FALSE POSITIVES

These five are silent on **both** sides when re-run, and pass cleanly in an empty directory. They
only failed during the suite because of a file the tester's own bash had created moments earlier.

Reproduced deliberately, with a non-executable `echo` file in the working directory:

```
$ printf '#!/bin/sh\n' > echo ; chmod 000 echo
$ printf 'export PATH=""\necho $PATH\n' | minishell
./echo: Permission denied              <- stderr, exit 126
$ printf 'export PATH=""\necho $PATH\n' | bash
                                       <- silent, exit 0
```

An empty or unset PATH means "the current directory", which is correct, and `./echo` is then found —
but only because of group 1: bash would never consult PATH for `echo` at all, since `echo` is a
builtin. So these five are artifacts of the test environment, with a real defect behind them.

| case | input | minishell stderr | bash stderr |
|---|---|---|---|
| `2_correction.sh:204` | `unset PATH\necho $PATH\nunset PATH\necho $PATH\n…` | *(silent)* | *(silent)* |
| `2_path_check.sh:12` | `unset PATH\necho 42\nunset PATH\nunset PATH\nuns…` | *(silent)* | *(silent)* |
| `2_path_check.sh:21` | `export PATH=""\necho $PATH\n` | *(silent)* | *(silent)* |
| `2_path_check.sh:35` | `export PATH=\necho $PATH\necho 1\n` | *(silent)* | *(silent)* |
| `2_path_check.sh:5` | `unset PATH\necho $PATH\n/bin/ls\necho 1\ncd -\ne…` | *(silent)* | *(silent)* |

## 7. bash complains, minishell stays quiet — 2 cases

The only two cases in the other direction, and both are bash features this shell does not have:

- `unset TES;T` — bash splits on `;`, tries to run `T`, and reports it missing. Minishell has no `;`
  (explicitly out of the subject) and unsets a variable literally named `TES;T`.
- `unset -TEST` — bash parses `-T` as an invalid option and prints a usage line. Minishell has no
  option parsing in `unset` and just tries to unset a name called `-TEST`.

Both also fail the EXIT_CODE column and are listed as the two survivors of the `unset` fix in
`todo/test_out_fix.md`.

| case | input | minishell stderr | bash stderr |
|---|---|---|---|
| `1_builtins.sh:552` | `unset TES;T\n` | *(silent)* | bash: line 2: T: command not found\n |
| `1_builtins.sh:566` | `unset -TEST\n` | *(silent)* | bash: line 2: unset: -T: invalid option\nunset: usage: unset [-f] [-v]… |

## 8. The two known regressions from this branch — 2 cases

Both already documented in `todo/test_out.md`; they show up here too because minishell now prints an
error where it previously printed nothing.

- `export TEST+=100` — the tightened identifier check rejects `+=`. Bash accepts it (append).
- `touch "` ⏎ `"` — the new unclosed-quote detection reports a syntax error. Bash joins the two
  lines into one command.

| case | input | minishell stderr | bash stderr |
|---|---|---|---|
| `1_builtins.sh:490` | `export TEST+=100\n` | export: `TEST+=100': not a valid identifier\n | *(silent)* |
| `1_scmds.sh:19` | `touch "\n"\n/bin/rm -f "\n"\n` | minishell: syntax error: unexpected end of file\n | *(silent)* |

---

## Noticed while reading the messages (not a tester failure)

Since the tester only checks *presence*, the wording is never compared — but it is inconsistent.
Some messages carry the `minishell: ` prefix and some do not:

| message | prefix? |
|---|---|
| `minishell: cd: --: No such file or directory` | yes |
| `minishell: cd: too many arguments` | yes |
| `export: \`TEST+=100': not a valid identifier` | no |
| `/bin/echo 42: No such file or directory` | no |
| `./echo: Permission denied` | no |
| `echo segfault \| grep segfault: command not found` | no |

Bash prefixes everything with `bash: ` (plus `line N:` in a script). An evaluator reading stderr
side by side will see the difference even though the tester does not. Nothing was changed for this
report — it is only an observation.
