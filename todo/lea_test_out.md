# `mstest --no-stdfds m` on the new tester — only the failures that are **new**

Branch **claus**, `1bc803c` (last commit touching C sources: `3f28229`; `make -q` confirms the
tested binary is current). Nothing was changed for this report — it is review only.

```
TOTAL TEST COUNT: 986   TESTS PASSED: 851
STD_OUT: 25   STD_ERR: 112   EXIT_CODE: 8   CRASHING: 0
```

**135 cases fail at least one column. 36 of them are already written up** in `todo/test_out.md`
and `std_err.md` and are not repeated here. **The remaining 99 are listed below.**

## Why the numbers moved so much

The tester is not the one the earlier reports used. Three changes matter:

1. **stderr is now compared by content**, not by presence. It strips `bash: ` / `bash: line N: `
   from bash and your own `minishell: ` prefix from yours, then diffs. That is why STD_ERR went
   24 → 112 while STD_OUT went 78 → 25.
2. **bash runs in POSIX mode** (`bash --posix`) unless `--non-posix` is passed.
3. The prompt, start message and exit message are filtered out of stdout before diffing, and a
   **CRASH** column was added — **0 crashes**.

`--no-stdfds` itself only relaxes valgrind's fd tracking, so with `m` (no leak checks) it has no
effect on the result.

The test files were also renamed and expanded (`1_builtins.sh` is now split into
`1_builtins_exit/_export/_pwd/_unset`, `8_syntax_errors.sh` grew from 114 to 221 lines, and
`11_expansion.sh` is new), so **`file:line` ids no longer match the old reports**. A case therefore
counts as "already known" only when its **command text** matches one recorded in the two earlier
reports — 146 distinct inputs were recovered from them for the comparison.

## How the 99 were validated

Each was re-run in an **empty directory** against your binary and against `bash --posix` with the
tester's own `enable -n .` prefix, and against a **`master` build** (`bdd8175`, throwaway worktree)
to separate pre-existing behaviour from anything the two claus commits changed.

**94 of the 99 behave identically on `master`** — they are pre-existing and simply were not
measured before, because the old tester never compared error text. The 5 that differ are all cases
where claus is *closer* to bash than master was; they are marked below.

## Summary

| # | Group | Cases | Verdict |
|---|---|---|---|
| A1 | syntax error: wording only (`sign` vs `token`, quote style) | 44 | **real**, message text |
| A2 | syntax error: also names a different token than bash | 41 | **real**, message text + token choice |
| B | `$HOME` as a command: `Permission denied` vs `Is a directory` | 1 | message text only, exit code matches |
| C | `exit` with an out-of-range number | 6 | **real bug**, no overflow check |
| D | redirect target that expands to nothing | 1 | **real gap**, no "ambiguous redirect" |
| E | heredoc terminated by EOF | 2 | **real gap**, missing warning |
| F | stderr ordering in a 55-stage pipeline | 1 | **false positive** (race) |
| G | command name with tabs: bash quotes it as `$'\t\t'` | 2 | message text only |
| H | `$notexists \| ls \| $notexists` | 1 | **false positive** (junk file in the project dir) |

**99 total.** 85 of them (A1 + A2) are the same defect seen 85 times.

---

## A. Syntax error messages — 85 cases

Every syntax test now fails, for two independent reasons.

**A1 — wording and quoting (44 cases).** The token named is the same as bash's; only the sentence
differs:

```
minishell:  syntax error near unexpected sign '|'
bash:       syntax error near unexpected token `|'
```

Two differences in one line: **`sign` instead of `token`**, and `'x'` instead of `` `x' `` (bash
opens with a backtick and closes with a single quote). The string lives in `ms_syntax_check`
(`src/ms_token.c`).

| case | input | minishell | bash |
|---|---|---|---|
| `1_pipelines.sh:138` | `\|ls \| ls\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `1_scmds.sh:108` | `\| echo -n oui\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `1_scmds.sh:110` | `\| \| \|\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:11` | `> > > > >\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:17` | `>> > >> > >>\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:21` | `<< << << << <\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`<<'\n` |
| `8_syntax_errors.sh:29` | `< < < < < <\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:45` | `echo \| \|\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:57` | `\|echo\|\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:61` | `\|\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:63` | `\| test\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:65` | `\| \| \|\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:67` | `\| \| \| \| test\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:69` | `\| test\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:73` | `hello world\n\| \| \| \| \| \| \| …` | `hello: command not found\nminishell: syntax er…` | `hello: command not found\nsyntax error near un…` |
| `8_syntax_errors.sh:83` | `\| echo -n oui\n` | `syntax error near unexpected sign '\|'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:107` | `echo >          >           < "ech…` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:109` | `echo >          >         \| echo …` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:111` | `echo >          >         \| echo …` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:113` | `echo <          <         > echo\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:115` | `echo <  < <         > ok\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:117` | `echo <  < \| echo ok\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:119` | `echo <  < \|    < ok\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:121` | `echo <      < \|    > echo\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:127` | `echo < < < echo seegf\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:129` | `echo > > < "echo"\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:131` | `echo > > \| echo kekw\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:133` | `echo > > \| echo super valid\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:135` | `echo < < > echo\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:137` | `echo < < < > ok\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:155` | `echo seg < < > echo segf\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:157` | `echo seg < < < > echo segf\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:163` | `echo < < \| echo ok\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:165` | `echo < < \| < ok\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:167` | `echo < < \| > echo\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:169` | `echo segfault < " < < < " < < amaz…` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:171` | `echo segfault <"    <   <   <"  < …` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:177` | `echo seg <      < > echo segf\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:179` | `echo seg <      < <    > echo segf…` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:181` | `echo <      <     < echo seegf\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:193` | `echo seg <<<<<>> echo segf\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`<<'\n` |
| `8_syntax_errors.sh:195` | `echo <<<<< echo seegf\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`<<'\n` |
| `8_syntax_errors.sh:199` | `ls \| cat << stop \| ls -la \| cat…` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:213` | `/bin/cat Makefile > out >>out1 >ou…` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>'\n` |

**A2 — a different token is named (41 cases).** Beyond the wording, minishell reports the *first*
operator it saw, while bash reports the token that actually broke the parse:

| input | minishell says | bash says | why |
|---|---|---|---|
| `<` | `'<'` | `` `newline' `` | bash names what followed the operator — the line ended |
| `>> >> >> >>` | `'>'` | `` `>>' `` | minishell stores only one character of a two-character operator |
| `<\| echo ok` | `'<'` | `` `\|' `` | the `\|` is the offending token, not the `<` |

The `>>`/`<<` half of this is the `ms_substr(str, i, len)` call in `handle_operator` keeping
`len = 1` for two-character operators — the token *value* stays `">"` even though the type is
`T_OUT_APPEND`. (Noted as harmless in the first plan, because back then the value was only used for
messages that nobody compared. The new tester compares them.)

| case | input | minishell | bash |
|---|---|---|---|
| `10_parsing_hell.sh:317` | `<\| echo ok\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:7` | `<\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`newline'\…` |
| `8_syntax_errors.sh:9` | `<<\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`newline'\…` |
| `8_syntax_errors.sh:13` | `>> >> >> >>\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>>'\n` |
| `8_syntax_errors.sh:15` | `>>>>>>>>>\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>>'\n` |
| `8_syntax_errors.sh:19` | `> >> > >> >\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`>>'\n` |
| `8_syntax_errors.sh:23` | `<< < << < <<\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:25` | `< << < << <\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`<<'\n` |
| `8_syntax_errors.sh:31` | `/bin/cat ><\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:33` | `/bin/cat <Makefile >\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`newline'\…` |
| `8_syntax_errors.sh:37` | `echo >\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`newline'\…` |
| `8_syntax_errors.sh:39` | `echo > <\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:51` | `>echo>\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`newline'\…` |
| `8_syntax_errors.sh:53` | `</bin/echo<\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`newline'\…` |
| `8_syntax_errors.sh:55` | `>>/usr/bin/echo>>\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`newline'\…` |
| `8_syntax_errors.sh:71` | `echo > <\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:76` | `cat wouaf wouaf\n>\n` | `cat: wouaf: No such file or directory\ncat: wo…` | `cat: wouaf: No such file or directory\ncat: wo…` |
| `8_syntax_errors.sh:93` | `<<\| echo wtf\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:95` | `>>\| echo wtf\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:97` | `<\| echo wtf\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:105` | `< >\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:123` | `echo >>\| echo super valid\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:125` | `echo >>< "echo"\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:139` | `echo >>\| echo kekw\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:141` | `echo <<\| echo ok\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:143` | `echo <<\|< ok\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:145` | `echo <<\|> echo\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:147` | `echo <<>> echo\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`>>'\n` |
| `8_syntax_errors.sh:149` | `echo <<> ok\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:151` | `echo seg < > echo seg\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:153` | `echo seg > < echo segf\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:159` | `echo segf > \| echo is this invali…` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:161` | `echo segf < \| < echo super valid\…` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:173` | `echo seg <  > echo seg\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:175` | `echo seg >  < echo segf\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:183` | `echo segf >     \| echo is this in…` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:185` | `echo segf <         \|        < ec…` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`\|'\n` |
| `8_syntax_errors.sh:187` | `echo seg < >> echo seg\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`>>'\n` |
| `8_syntax_errors.sh:189` | `echo seg >< echo segf\n` | `syntax error near unexpected sign '>'\n` | `syntax error near unexpected token \`<'\n` |
| `8_syntax_errors.sh:191` | `echo seg <<> echo segf\n` | `syntax error near unexpected sign '<<'\n` | `syntax error near unexpected token \`>'\n` |
| `8_syntax_errors.sh:197` | `echo segf <\|< echo super valid\n` | `syntax error near unexpected sign '<'\n` | `syntax error near unexpected token \`\|'\n` |

## B. `$HOME` as a command — 1 case

Both shells exit **126**, only the sentence differs: `execve` fails with `EACCES` on a directory and
minishell prints `strerror(errno)`, while bash special-cases it.

```
minishell:  /home/stmuller: Permission denied
bash:       /home/stmuller: Is a directory
```

*Differs from master*, which never expanded the command word and said
`$HOME: command not found` with exit 127 — so claus is the closer of the two, and this case only
became visible because the expansion fix landed.

| case | input | minishell | bash |
|---|---|---|---|
| `8_syntax_errors.sh:27` | `$HOME\n` | /home/stmuller: Permission denied\n | /home/stmuller: Is a directory\n |

## C. `exit` with an out-of-range number — 6 cases — REAL BUG

`ms_atoi_valid` only checks that the characters are digits, and `ms_atoi` accumulates into a
`t_byte`, so a number too large for a `long` is accepted and wraps:

| input | minishell | bash |
|---|---|---|
| `exit 9223372036854775808` | exits **0**, silent | `exit: 9223372036854775808: numeric argument required`, exits 2 |
| `exit -9223372036854775809` | exits **255**, silent | same message, exits 2 |
| `exit 111…1` (128 digits) | exits **199**, silent | same message, exits 2 |
| `exit 999…9` (128 digits) | exits **255**, silent | same message, exits 2 |

Bash's rule is `LLONG_MIN…LLONG_MAX`, then mod 256. Same behaviour on master — pre-existing, and not
something the earlier `exit` fix covered, since that one only handled non-numeric text.

| case | input | minishell | bash |
|---|---|---|---|
| `1_builtins_exit.sh:111` | `exit 11111111111111111111111111111111111…` | *(silent)* | exit: 11111111111111111111111111111111111111111111… |
| `1_builtins_exit.sh:113` | `exit 99999999999999999999999999999999999…` | *(silent)* | exit: 99999999999999999999999999999999999999999999… |
| `1_builtins_exit.sh:117` | `exit 9223372036854775808\n` | *(silent)* | exit: 9223372036854775808: numeric argument requir… |
| `1_builtins_exit.sh:121` | `exit -9223372036854775809\n` | *(silent)* | exit: -9223372036854775809: numeric argument requi… |
| `1_builtins_exit.sh:125` | `exit 00000000000000000000000000000000000…` | *(silent)* | exit: 00000000000000000000000000000000000000000000… |
| `1_builtins_exit.sh:129` | `exit -0000000000000000000000000000000000…` | *(silent)* | exit: -0000000000000000000000000000000000000000000… |

## D. Redirect target that expands to nothing — 1 case — REAL GAP

```
> $notexists echo "haha"
minishell:  haha: command not found          (exit 127)
bash:       $notexists: ambiguous redirect   (exit 1)
```

`$notexists` disappears, so minishell shifts everything left: `echo` becomes the file to write and
`haha` becomes the command. Bash refuses to guess and calls it an ambiguous redirect. Pre-existing.

| case | input | minishell | bash |
|---|---|---|---|
| `11_expansion.sh:11` | `> $notexists echo "haha"\n` | haha: command not found\n | $notexists: ambiguous redirect\n |

## E. Heredoc terminated by end of file — 2 cases — REAL GAP

When the input ends before the delimiter arrives, bash warns and carries on with what it has;
minishell accepts it silently. Both keep the same exit code, so only stderr differs.

```
bash: warning: here-document at line 2 delimited by end-of-file (wanted `lala')
```

Pre-existing.

| case | input | minishell | bash |
|---|---|---|---|
| `1_pipelines.sh:96` | `ls \| cat << stop \| ls -la \| cat << st…` | *(silent)* | warning: here-document at line 11 delimited by end… |
| `1_redirs.sh:261` | `echo test \|  <<lala\n` | *(silent)* | warning: here-document at line 2 delimited by end-… |

## F. stderr ordering in a 55-stage pipeline — 1 case — FALSE POSITIVE

`aaa | bbb | aaa | …` with 55 stages. Every message is present in both shells and the **multiset is
identical**; only the interleaving differs, because 55 children write to the same stderr
concurrently. Five consecutive runs of minishell produced **five different orderings**, so no fix
can make this deterministic — and bash's own order is equally arbitrary.

| case | input | minishell | bash |
|---|---|---|---|
| `1_pipelines.sh:180` | `aaa \| bbb \| aaa \| bbb \| aaa \| bbb \…` | aaa: command not found\naaa: command not found\nbb… | aaa: command not found\nbbb: command not found\naa… |

## G. Command name containing tabs — 2 cases

Bash renders non-printable characters in its error using `$'…'` quoting; minishell prints the raw
bytes:

```
minishell:  \t\t: command not found
bash:       $'\t\t': command not found
```

*Differs from master*, which printed `"\t\t": command not found` — it never removed the quotes
from the command word. Claus names the command correctly now; only bash's escaping of the tabs is
missing.

| case | input | minishell | bash |
|---|---|---|---|
| `2_correction.sh:15` | `"\t\t"\n` | \t\t: command not found\n | $'\\t\\t': command not found\n |
| `2_correction.sh:17` | `"\t\t\t"\n` | \t\t\t: command not found\n | $'\\t\\t\\t': command not found\n |

## H. `$notexists | ls | $notexists` — 1 case — FALSE POSITIVE

Re-run in an empty directory, minishell and bash agree exactly: no output, exit 0. During the suite
the middle `ls` printed `echo` — a junk file the tester's own bash had created moments earlier with
`>| echo …`, the same contamination documented in `todo/test_out.md`. *Differs from master*, which
also printed `$notexists: command not found`; claus is silent, like bash.

| case | input | minishell | bash |
|---|---|---|---|
| `11_expansion.sh:5` | `$notexists \| ls \| $notexists\n` | echo\n | *(silent)* |

---

## Not repeated here

36 of the 135 failing cases are already covered by the two earlier reports — `$"…"`/`$'…'` quoting,
backslashes, word splitting, `~`, `export` formatting, the builtin-vs-PATH precedence, `cd --`,
`2>`, and the two known regressions from the branch work. They are unchanged.
