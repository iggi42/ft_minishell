# `mstest vm` on branch `claus` — failing cases, validated

Run on branch **claus** (commit `153adc7`), binary rebuilt from that commit, whole mandatory
suite with valgrind: `mstest vm`.

```
TOTAL TEST COUNT: 941   TESTS PASSED: 787   LEAKING: 0
STD_OUT: 80   STD_ERR: 29   EXIT_CODE: 72
```

**STD_ERR is ignored** as requested. STD_OUT and EXIT_CODE failures together come from
**145 distinct cases** (a case can fail both). All 145 are listed below.

## How each case was validated

The tester's verdict alone is not trusted. Every one of the 145 cases was:

1. **re-run individually** — same input, same `enable -n .` prefix bash gets from the tester —
   against the `claus` binary and against real bash;
2. **re-run against a `master` build** (built from commit `bdd8175` in a throwaway worktree, run
   with the project directory as cwd) to tell "was already broken" from "my branch broke it";
3. **re-run in an empty scratch directory** for everything that touches PATH, the cwd or file
   creation, because the tester runs all 941 cases *inside the project directory* and its own
   bash leaves junk files there.

That third step matters: during the run, the tester's bash executes `>| echo sure` and
`>| echo wtf`, which **create a file called `echo` in the project root**, and an earlier run had
already left an empty but **executable** file called `ls` there. Once a PATH entry means "current
directory", those junk files shadow the `echo` builtin and `/bin/ls`. Several "failures" are only
that.

## Verdict summary

| # | Group | Cases | Verdict |
|---|---|---|---|
| 1 | `unset` always returns 1 | 40 | **real bug**, pre-existing |
| 2 | `$"..."` / `$'...'` quoting | 31 | bash extension, not in the subject |
| 3 | no word splitting after expansion | 17 | known gap, not in the subject |
| 4 | backslash escaping | 14 | not in the subject |
| 5 | failed `execve` reports 126, bash says 127 | 13 | **real bug**, pre-existing |
| 6 | tester junk files in the project dir | 8 | **false positive** |
| 7 | environment noise (`SHLVL`, `_`, `env -i` locale) | 5 | **false positive** |
| 8 | `~` tilde expansion | 5 | not implemented, not in the subject |
| 9 | `export` with option-like names exit code | 3 | cosmetic, pre-existing |
| 10 | `>\|` clobber operator | 2 | bash extension |
| 11 | heredoc delimiter with embedded quotes | 2 | **real bug**, pre-existing |
| 12 | `export` with no arguments output format | 1 | known, pre-existing |
| 13 | `export TEST+=100` | 1 | **regression from this branch** |
| 14 | multi-line quoted string | 1 | **regression from this branch** |
| 15 | `cd --` | 1 | cosmetic, pre-existing |
| 16 | `2>` fd-prefixed redirection | 1 | not in the subject |

**145 total.** Nothing leaks: 0 leaking cases out of 941 valgrind runs.

---

## A. Regressions introduced by this branch (2)

These two are the only cases that fail on `claus` and pass on `master` for a real reason.

### A1 — `export TEST+=100` now rejected

| | |
|---|---|
| case | `1_builtins.sh:490` |
| claus | exit **1**, `export: \`TEST+=100': not a valid identifier` |
| master | exit 0 |
| bash | exit 0, sets `TEST=100` |

Cause: the widened identifier check in `import_var` rejects anything whose name is not followed by
`=` or end-of-string, and `+` is not allowed. Bash supports `+=` (append). Note what master
actually did here: it silently created a variable **with an empty name**, so `env` printed `==100`.
So master passes the test by doing something worse; neither implements `+=`.

### A2 — quoted string continued on the next line

| | |
|---|---|
| case | `1_scmds.sh:19` — `touch "` ⏎ `"` then `/bin/rm -f "` ⏎ `"` |
| claus | exit **2**, `minishell: syntax error: unexpected end of file` |
| master | exit 0, silently did nothing |
| bash | exit 0, creates and removes a file whose name is a newline |

Cause: the new unclosed-quote detection. Bash joins the two lines into one command; minishell reads
line by line, so the first line really is an unterminated quote, and the shell now reports it and
exits 2 in script mode (which is what bash does for a genuinely unterminated quote at EOF). Master
"passed" only because it silently ignored the line.

## B. Newly exposed, but not new (1)

### B1 — `"."` reports 126 where bash says 127

| | |
|---|---|
| case | `1_scmds.sh:84` |
| claus | exit 126, `/home/stmuller/.local/bin/.: Permission denied` |
| master | exit 127, `".": command not found` |
| bash | exit 127 |

Master only differs because it never removed the quotes from the command word (that was bug 1).
Plain `.` without quotes gives **126 on master too**, so the defect is pre-existing: the PATH search
accepts a *directory* as an executable, because every directory contains `.` and `access(X_OK)`
succeeds on directories. Same family as group 5 below.

---

## 1. `unset` always returns 1 — 40 cases — REAL BUG, pre-existing

`ms_exec_builtin_unset` sets the status to 1 whenever `ms_env_unset` reports the name was not
present. Bash's `unset` returns **0** for a name that does not exist, and for names it rejects it
only complains on stderr. Verified by hand in a clean directory:

```
unset doesntexist   bash-> 0    minishell-> 1
unset TES-T         bash-> 0    minishell-> 1
unset ""            bash-> 0    minishell-> 1
unset export        bash-> 0    minishell-> 1
```

This single behaviour is **28% of all failing cases**. Three of them
(`2_correction.sh:204`, `2_path_check.sh:5`, `2_path_check.sh:12`) are listed under group 6
instead, because they fail for the junk-file reason, not for this one.

| case | fails | input |
|---|---|---|
| `1_builtins.sh:518` | exit | `unset ""\n` |
| `1_builtins.sh:520` | exit | `unset =\n` |
| `1_builtins.sh:522` | exit | `unset "="\n` |
| `1_builtins.sh:524` | exit | `unset ""=\n` |
| `1_builtins.sh:526` | exit | `unset =""\n` |
| `1_builtins.sh:528` | exit | `unset ==\n` |
| `1_builtins.sh:534` | exit | `unset $\n` |
| `1_builtins.sh:536` | exit | `unset "$"\n` |
| `1_builtins.sh:538` | exit | `unset $""\n` |
| `1_builtins.sh:542` | exit | `unset doesntexist\n` |
| `1_builtins.sh:552` | exit | `unset TES;T\n` |
| `1_builtins.sh:554` | exit | `unset TES.T\n` |
| `1_builtins.sh:556` | exit | `unset TES+T\n` |
| `1_builtins.sh:558` | exit | `unset TES=T\n` |
| `1_builtins.sh:560` | exit | `unset TES}T\n` |
| `1_builtins.sh:562` | exit | `unset TES{T\n` |
| `1_builtins.sh:564` | exit | `unset TES-T\n` |
| `1_builtins.sh:566` | exit | `unset -TEST\n` |
| `1_builtins.sh:568` | exit | `unset _TEST\n` |
| `1_builtins.sh:570` | exit | `unset TES_T\n` |
| `1_builtins.sh:572` | exit | `unset TEST_\n` |
| `1_builtins.sh:574` | exit | `unset TE*ST\n` |
| `1_builtins.sh:576` | exit | `unset TES#T\n` |
| `1_builtins.sh:578` | exit | `unset TES@T\n` |
| `1_builtins.sh:580` | exit | `unset TES!T\n` |
| `1_builtins.sh:582` | exit | `unset TES$?T\n` |
| `1_builtins.sh:584` | exit | `unset ============\n` |
| `1_builtins.sh:586` | exit | `unset +++++++\n` |
| `1_builtins.sh:588` | exit | `unset ________\n` |
| `1_builtins.sh:590` | exit | `unset export\n` |
| `1_builtins.sh:592` | exit | `unset echo\n` |
| `1_builtins.sh:594` | exit | `unset pwd\n` |
| `1_builtins.sh:596` | exit | `unset cd\n` |
| `1_builtins.sh:598` | exit | `unset unset\n` |
| `1_builtins.sh:600` | exit | `unset sudo\n` |
| `1_builtins.sh:602` | exit | `unset TES^T\n` |
| `1_builtins.sh:604` | exit | `unset TES!T\n` |
| `1_builtins.sh:606` | exit | `unset TES\\~T\n` |
| `1_variables.sh:32` | exit | `export a="asd" b="de" o= c="hellomi" X\nunset o asd B x X wqd c\n` |
| `2_correction.sh:202` | exit | `unset env\n` |

## 2. `$"..."` and `$'...'` — 31 cases — bash extension, not required

`$"text"` is bash's locale translation and `$'text'` is ANSI-C quoting. Minishell sees `$` followed
by a character that cannot start a variable name, keeps the `$` and then removes the quotes, so it
prints `$HOME` where bash prints `HOME`. Neither form is part of the mandatory subject.

| case | fails | input |
|---|---|---|
| `0_compare_parsing.sh:26` | stdout | `/bin/echo $"HOME"$USER\n` |
| `0_compare_parsing.sh:28` | stdout | `/bin/echo $"HOM"E$USER\n` |
| `0_compare_parsing.sh:32` | stdout | `/bin/echo $"HOME"\n` |
| `0_compare_parsing.sh:34` | stdout | `/bin/echo $"42$"\n` |
| `10_parsing_hell.sh:297` | stdout | `echo '$'$'$'$'$'\n` |
| `10_parsing_hell.sh:299` | stdout | `echo '$'$'$'$'$'$'$'\n` |
| `10_parsing_hell.sh:301` | stdout | `echo "$"$\'$\'$"$"$"$"$\'$\'\n` |
| `1_builtins.sh:31` | stdout | `echo $"HOME"$USER\n` |
| `1_builtins.sh:33` | stdout | `echo $"HOM"E$USER\n` |
| `1_builtins.sh:37` | stdout | `echo $"HOME"\n` |
| `1_builtins.sh:39` | stdout | `echo $"42$"\n` |
| `1_variables.sh:40` | stdout | `/bin/echo $"HOME"$USER\n` |
| `1_variables.sh:42` | stdout | `/bin/echo $"HOM"E$USER\n` |
| `1_variables.sh:44` | stdout | `/bin/echo $"\'HOM\'E"$USER\n` |
| `1_variables.sh:46` | stdout | `/bin/echo $'HOM'E$USER\n` |
| `1_variables.sh:48` | stdout | `/bin/echo $"HOME"\n` |
| `1_variables.sh:50` | stdout | `/bin/echo $'HOME'\n` |
| `1_variables.sh:60` | stdout | `/bin/echo $"$"\n` |
| `1_variables.sh:62` | stdout | `/bin/echo $"42$"\n` |
| `1_variables.sh:66` | stdout | `/bin/echo $'$'\n` |
| `2_correction.sh:129` | stdout | `echo $"HOME"\n` |
| `2_correction.sh:131` | stdout | `echo $'HOME'\n` |
| `2_correction.sh:139` | stdout | `echo $"HOME"$USER\n` |
| `2_correction.sh:141` | stdout | `echo $"HOM"E$USER\n` |
| `2_correction.sh:143` | stdout | `echo $"\'HOM\'E"$USER\n` |
| `2_correction.sh:145` | stdout | `echo $'HOM'E$USER\n` |
| `2_correction.sh:147` | stdout | `echo $"HOME"\n` |
| `2_correction.sh:149` | stdout | `echo $'HOME'\n` |
| `2_correction.sh:159` | stdout | `echo $"$"\n` |
| `2_correction.sh:161` | stdout | `echo $"42$"\n` |
| `2_correction.sh:165` | stdout | `echo $'$'\n` |

## 3. No word splitting after expansion — 17 cases — known gap, not required

`export X="  A  B  "` then `echo "1"$X'2'` gives `1  A  B  2` here and `1 A B 2` in bash, because
bash splits the expanded value on whitespace and re-joins with single spaces. The same gap makes
`$T` unusable as a command when the variable holds `cmd arg`. The project's own TODO listed this
("TODO word splitting?"); the mandatory subject does not ask for it.

`1_variables.sh:120` improved on this branch (it now prints `42 42` instead of nothing, because the
command word is expanded at last) but still fails, since bash prints three lines.

| case | fails | input |
|---|---|---|
| `10_parsing_hell.sh:96` | stdout | `export T="-n test1 -n test 2"\necho $T\n` |
| `10_parsing_hell.sh:216` | stdout/exit | `export T="echo segfault \| grep segfault"\n$T\n` |
| `10_parsing_hell.sh:219` | stdout | `export T=-nnnnnnnn"nnnnnnn "\necho $T\n` |
| `1_variables.sh:120` | stdout | `export tmp_test="/bin/echo 42"\n$tmp_test\n$tmp_test 42\nexport tmp_test="/bin/echo"\n$t…` |
| `1_variables.sh:130` | stdout | `export X="  A  B  "\n/bin/echo "1"$X\'2\'\n` |
| `1_variables.sh:133` | stdout | `export X=" A  B  "\n/bin/echo "1"$X\'2\'\n` |
| `1_variables.sh:136` | stdout | `export X="A  B  "\n/bin/echo "1"$X\'2\'\n` |
| `1_variables.sh:139` | stdout | `export X="  A  B "\n/bin/echo "1"$X\'2\'\n` |
| `1_variables.sh:142` | stdout | `export X="  A  B"\n/bin/echo "1"$X\'2\'\n` |
| `1_variables.sh:145` | stdout | `export X="  A B  "\n/bin/echo "1"$X\'2\'\n` |
| `1_variables.sh:148` | stdout | `export X="  AB  "\n/bin/echo "1"$X\'2\'\n` |
| `1_variables.sh:151` | stdout | `export X="  A  B  "\n/bin/echo $X\'2\'\n` |
| `1_variables.sh:154` | stdout | `export X="  A  B  "\n/bin/echo $X"1"\n` |
| `1_variables.sh:163` | stdout | `export X="   "\n/bin/echo "1"$X\'2\'\n` |
| `1_variables.sh:166` | stdout | `export X="  A  B  "\n/bin/echo ?$X\'2\'\n` |
| `1_variables.sh:169` | stdout | `export X="  A  B  "\n/bin/echo "1"$X?\n` |
| `9_go_wild.sh:30` | stdout | `export test="arg1\targ2"\necho \'echo $1\' > tmp_test_sh\nbash tmp_test_sh $test\necho \…` |

## 4. Backslash escaping — 14 cases — not required

`echo \\$USER` prints `\stmuller` here and `$USER` in bash. The subject explicitly excludes `\`
and `;` handling.

| case | fails | input |
|---|---|---|
| `0_compare_parsing.sh:52` | stdout | `/bin/echo \\$USER\n` |
| `0_compare_parsing.sh:54` | stdout | `/bin/echo \\\\$USER\n` |
| `0_compare_parsing.sh:56` | stdout | `/bin/echo \\\\\\$USER\n` |
| `0_compare_parsing.sh:58` | stdout | `/bin/echo \\\\\\\\$USER\n` |
| `0_compare_parsing.sh:60` | stdout | `/bin/echo \\\\\\\\\\$USER\n` |
| `0_compare_parsing.sh:62` | stdout | `/bin/echo \\\\\\\\\\\\\\\\\\$USER\n` |
| `0_compare_parsing.sh:64` | stdout | `/bin/echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \\$PAT…` |
| `1_builtins.sh:59` | stdout | `echo \\$USER\n` |
| `1_builtins.sh:61` | stdout | `echo \\\\$USER\n` |
| `1_builtins.sh:63` | stdout | `echo \\\\\\$USER\n` |
| `1_builtins.sh:65` | stdout | `echo \\\\\\\\$USER\n` |
| `1_builtins.sh:67` | stdout | `echo \\\\\\\\\\$USER\n` |
| `1_builtins.sh:69` | stdout | `echo \\\\\\\\\\\\\\\\\\$USER\n` |
| `1_builtins.sh:71` | stdout | `echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \\$PATH \\\…` |

## 5. A failed `execve` reports 126 instead of 127 — 13 cases — REAL BUG, pre-existing

`ms_execve` always exits with `EXIT_NO_EXEC_PERM` (126), whatever `errno` says. Bash distinguishes:
`ENOENT` → 127 with "No such file or directory", `EACCES` → 126 with "Permission denied". Verified
in a clean directory:

```
/bin/cats   ->  minishell 126 | bash 127     (does not exist)
./np (000)  ->  minishell 126 | bash 126     (exists, not executable — already correct)
```

Two sub-cases fold in here: a directory found on PATH is treated as executable (`.`, `..`, `/ls/`),
and an empty-but-executable file gives `Exec format error` where bash falls back to `/bin/sh`
(`./ls`, `"./"ls`, … — those four only fail because of the junk `ls` file, see group 6).

| case | fails | input |
|---|---|---|
| `1_scmds.sh:38` | exit | `'/bin/echo test1'\n` |
| `1_scmds.sh:84` | exit | `"."\n` |
| `1_scmds.sh:88` | exit | `./ls\n` |
| `1_scmds.sh:90` | exit | `"./"ls\n` |
| `1_scmds.sh:92` | exit | `"./""ls"\n` |
| `1_scmds.sh:94` | exit | `"./"\'\'"ls"\n` |
| `1_scmds.sh:100` | exit | `/ls\n` |
| `1_scmds.sh:104` | exit | `/ls/\n` |
| `1_scmds.sh:108` | exit | `/bin/cats\n` |
| `1_scmds.sh:110` | exit | `./4242424242.sh\n` |
| `2_correction.sh:61` | exit | `/bin/exe42 42\n` |
| `8_syntax_errors.sh:33` | exit | `.\n` |
| `8_syntax_errors.sh:35` | exit | `..\n` |

## 6. Junk files the tester leaves in the project directory — 8 cases — FALSE POSITIVES

All eight pass when the same input is run in an empty directory, with output and exit code
identical to bash and to master:

```
unset PATH; echo $?              clean dir -> minishell 0 | bash 0    (tester: 126)
export PATH=""; echo $PATH       clean dir -> minishell 0 | bash 0    (tester: 126)
unset PATH; echo $PATH; /bin/ls  clean dir -> identical to bash       (tester: 126)
```

Why they fail inside the project directory: the tester's own bash runs `>| echo sure` and
`>| echo wtf`, which create a file named **`echo`** next to the binary, and an earlier tester run
had left an empty but **executable** file named **`ls`** there. (Both are gone now: later cases in
the same run delete them again, e.g. `/bin/rm -rf echo`. So a second run can score these cases
differently depending on when each junk file exists — they are not deterministic.) An empty or unset
PATH now correctly means "the current directory", so minishell finds `./echo` and `./ls` and tries
to execute them — while bash never consults PATH for `echo`, because `echo` is a builtin and
builtins win over PATH in bash.

Two genuine observations hide behind this artifact, worth knowing but not fixed:
minishell looks a command up on PATH **before** checking its builtins (bash does the opposite), and
it has no `/bin/sh` fallback for `ENOEXEC`.

| case | fails | input |
|---|---|---|
| `1_scmds.sh:69` | stdout/exit | `asd\nunset PATH\necho $?\n` |
| `2_correction.sh:204` | stdout/exit | `unset PATH\necho $PATH\nunset PATH\necho $PATH\nunset HOME\necho $HOME\n` |
| `2_path_check.sh:5` | stdout/exit | `unset PATH\necho $PATH\n/bin/ls\necho 1\ncd -\necho 42\n` |
| `2_path_check.sh:12` | stdout/exit | `unset PATH\necho 42\nunset PATH\nunset PATH\nunset PATH\necho $PATH\necho 1\necho 42\n` |
| `2_path_check.sh:21` | stdout/exit | `export PATH=""\necho $PATH\n` |
| `2_path_check.sh:35` | stdout/exit | `export PATH=\necho $PATH\necho 1\n` |
| `2_path_check.sh:47` | stdout | `touch tmp_x_file1\ntmp_x_file1\necho $?\n./tmp_x_file1\necho $?\nexport PATH=$HOME\necho…` |
| `2_path_check.sh:68` | exit | `export PATH=""\nls\n` |

## 7. Environment noise — 5 cases — FALSE POSITIVES

Comparisons of the whole environment between two different shells:
`SHLVL` differs by one, `_` is set by bash but not by minishell, `SHELL=minishell` is deliberate,
and `env -i ./minishell` runs a nested shell without `LANG`, so `ls` sorts in a different collation
order. Nothing to fix.

| case | fails | input |
|---|---|---|
| `1_pipelines.sh:8` | stdout | `env \| sort \| grep -v SHLVL \| grep -v ^_\n` |
| `1_pipelines.sh:32` | stdout | `/bin/env \| grep "_="\n` |
| `1_pipelines.sh:34` | stdout | `/bin/env \| grep "SHLVL"\n` |
| `2_correction.sh:171` | stdout | `env \| grep $USER\n` |
| `2_path_check.sh:43` | stdout | `env -i ./minishell\ncd /bin/\nls\n` |

## 8. `~` is not expanded — 5 cases — not in the mandatory subject

| case | fails | input |
|---|---|---|
| `1_builtins.sh:7` | stdout | `echo cd ~\n` |
| `1_builtins.sh:314` | stdout | `pwd\ncd ~\ncd - ananas dot jpeg\npwd\n` |
| `1_builtins.sh:337` | stdout | `pwd\ncd ~\npwd\n` |
| `2_path_check.sh:30` | exit | `cd ~\n` |
| `8_syntax_errors.sh:19` | exit | `~\n` |

## 9. `export` with option-like names — 3 cases — cosmetic

`export -TEST=100` exits 1 here, bash exits 2 (it treats `-T` as an invalid option). Both refuse.

| case | fails | input |
|---|---|---|
| `1_builtins.sh:420` | exit | `export --TEST=123\n` |
| `1_builtins.sh:430` | exit | `export -TEST=100\n` |
| `1_builtins.sh:460` | exit | `export -TEST=123\n` |

## 10. `>|` clobber operator — 2 cases — bash extension

`>| echo sure` is bash's "override noclobber" redirection. Minishell reports a syntax error (exit 2);
bash redirects into a file called `echo` and then fails to find `sure` (exit 127 / 0). Rejecting it
is defensible — but note this is what creates the junk `echo` file behind group 6.

| case | fails | input |
|---|---|---|
| `10_parsing_hell.sh:319` | exit | `>\| echo sure\n` |
| `8_syntax_errors.sh:100` | exit | `>\| echo wtf\n/bin/rm -rf echo\n` |

## 11. Heredoc delimiter with embedded quotes — 2 cases — REAL BUG, pre-existing

`unquoted_delimiter()` only recognises a delimiter that is quoted **as a whole** (`"EOF"`), so
`<< lim''` and `<< "$US"E"R"` are not matched: minishell keeps expanding the body and never finds
its terminator, then swallows the rest of the input.

| case | fails | input |
|---|---|---|
| `10_parsing_hell.sh:45` | stdout | `cat << "$US"E"R"\nbecause\nwe\nlove\nbash\n$USER\n` |
| `1_redirs.sh:229` | stdout | `cat << lim''\n$USER\n$NOVAR\n$HOME\nlim\n` |

## 12. `export` with no arguments — 1 case — known, pre-existing

Prints `export 'NAME=value'` in insertion order; bash prints `declare -x NAME="value"` sorted.
Already noted in the deleted `TODO.md`.

| case | fails | input |
|---|---|---|
| `1_builtins.sh:390` | stdout | `export\n` |

## 13. `cd --` — 1 case — cosmetic

Bash treats `--` as "end of options" and goes to `$HOME` (exit 0); minishell tries `chdir("--")`
and fails (exit 1).

| case | fails | input |
|---|---|---|
| `10_parsing_hell.sh:321` | exit | `cd --\n` |

## 14. `2>` fd-prefixed redirection — 1 case — not in the subject

`cd '/////' 2>/dev/null` — the tokenizer has no notion of a leading fd, so `2` becomes a third
argument to `cd` and `cd` complains about too many arguments (exit 1). The mandatory subject only
requires `<`, `>`, `<<` and `>>`.

| case | fails | input |
|---|---|---|
| `1_builtins.sh:233` | exit | `cd '/////' 2>/dev/null\n` |

---

## What I did **not** touch

No source file was modified for this report; the working tree is exactly the `claus` commit
(`153adc7`) plus your own pending `TODO.md` deletion. The only things written were this file and
scratch data outside the repository.

One side effect worth knowing about, caused by the tester and not by me: the run deleted the
untracked junk files `ls` and `echo` that were sitting in the project root (test cases run
`/bin/rm -rf echo` and friends), and it recreated and removed its own `tmp_out_*` / `tmp_err_*` /
`tmp_valgrind-out.txt` scratch files. Nothing tracked by git was touched — `git status` shows only
your pending `TODO.md` deletion and the untracked `bugs.txt`, `norm.pdf`, `plan.md` and this file.
