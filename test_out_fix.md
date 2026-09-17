# Fix log — groups 1, 5 and 11 from `test_out_c.md`

Branch **claus**. Three groups fixed with the smallest change that does the job; nothing else
was touched. Result on the same tester (`mstest`, mandatory suite, 941 cases):

| | before | after |
|---|---|---|
| TESTS PASSED | 787 | **841** (+54) |
| STD_OUT failures | 80 | 78 |
| EXIT_CODE failures | 72 | **20** |
| distinct failing cases (stdout/exit) | 145 | **91** |
| LEAKING (valgrind, per case) | 0 | **0** |
| newly broken cases | — | **0** |

Every change is listed below with the reason, the exact hunk, and what it does to the suite.

---

## Fix 1 — group 1: `unset` reported failure for a name that was not set

**File:** `src/ms_exec_builtins_unset.c` — 2 lines replaced by 1, plus a comment.

```diff
+// bash reports success even when the name was never set
 static void	*folding_unset(void *acc, t_arr_el el)
 {
-	if (!ms_env_unset((char *)el))
-		*(t_byte *)acc = 1;
+	ms_env_unset((char *)el);
 	return (acc);
 }
```

**Why.** `ms_env_unset` returns false when the key was not in the store, and the fold turned that
into exit status 1. Bash does not: `unset` succeeds whether or not the name existed, and it also
returns 0 for names it refuses (it only complains on stderr). Measured on the bash the tester
compares against (GNU bash 5.1.16):

```
unset doesntexist   bash-> 0     unset TES-T   bash-> 0
unset ""            bash-> 0     unset export  bash-> 0
```

The accumulator is now never written, so `ms_exec_builtin_unset` keeps returning its initial 0.
The `result` variable and `ft_arr_fold` call are left exactly as they were — removing them would
have been a bigger change for no gain.

**Effect:** 38 of the 40 cases in this group now match bash.

**Still failing (2), both outside the fix:**

| case | input | bash | minishell |
|---|---|---|---|
| `1_builtins.sh:552` | `unset TES;T` | 127 | 0 |
| `1_builtins.sh:566` | `unset -TEST` | 2 | 0 |

`;` is a command separator that this shell deliberately does not implement (bash runs `T` and
fails to find it), and `-TEST` is rejected by bash as an *invalid option*, which would mean adding
option parsing to `unset`. Both were failing before too, just with a different number (1 instead
of 0).

---

## Fix 2 — group 5: a failed `execve` always reported 126

Two small changes were needed, because the group had two different causes.

### 2a — the exit code follows `errno`

**File:** `src/ms_exec_child.c` — 2 lines added.

```diff
 static void	ms_execve(char *path, char **argv)
 {
 	execve(path, argv, ms_env_environ_export());
+	if (errno == ENOENT)
+		ms_error_out(EXIT_CMD_NOT_FOUND, path, errno);
 	ms_error_out(EXIT_NO_EXEC_PERM, path, errno);
 }
```

**Why.** `ms_execve` exited with `EXIT_NO_EXEC_PERM` (126) whatever went wrong. Bash separates the
two cases: a command that does not exist is 127, a command that exists but cannot be run is 126.
`ENOENT` is exactly "there is no such file", so it maps to `EXIT_CMD_NOT_FOUND` (127); everything
else keeps the old 126. Both constants already existed in `inc/ms_exec_utils.h` and `<errno.h>` was
already included, so nothing else had to change.

This fixes the explicit-path cases: `/bin/cats`, `/ls`, `/ls/`, `./4242424242.sh`, `/bin/exe42 42`,
`'/bin/echo test1'`, `./ls`, `"./"ls`, `"./""ls"`, `"./"''"ls"`.

### 2b — a directory found on PATH is not a command

**File:** `src/ms_exec_utils.c` — 1 new static function, 1 changed line, 1 include.

```diff
+#include <sys/stat.h>
```

```diff
+// a directory is X_OK for access(), but it is not a command:
+// dropping it here lets the caller report 127, like bash does
+static char	*drop_dir(char *path)
+{
+	struct stat	info;
+
+	if (path == NULL || stat(path, &info) != 0)
+		return (path);
+	if (!S_ISDIR(info.st_mode))
+		return (path);
+	return (ft_free(path), NULL);
+}
+
 char	*ms_find_exec_file(char *cmd0)
 {
 	char	*path;

 	if (!ms_is_path(cmd0))
-		path = ms_search_path(cmd0);
+		path = drop_dir(ms_search_path(cmd0));
 	else
 		path = ms_strdup(cmd0);
 	return (path);
 }
```

**Why.** `.` and `..` are not files, but every directory contains an entry called `.`, and
`access("/usr/bin/.", X_OK)` succeeds because directories carry the execute bit. So the PATH search
happily "found" `.`, `execve` failed with `EACCES`, and the shell reported 126 where bash reports
127 — bash skips non-regular files while searching PATH.

The check is deliberately **not** inside `ms_search_path`: that function is already exactly at the
norm's 25-line limit, and it would also have had to be applied twice (once for the `X_OK` hit and
once for the `F_OK` fallback). Filtering the single value it returns costs one wrapper and leaves
the search loop untouched.

It is applied **only** to the PATH-searched branch. An explicit path to a directory (`./somedir`,
`/tmp`) must keep reporting 126 "Is a directory", which is what bash does, and that path still goes
straight to `ms_strdup(cmd0)`.

**Effect:** all 13 cases in this group now match bash, including `.`, `..` and `"."`.

---

## Fix 3 — group 11: heredoc delimiter with embedded quotes

**File:** `src/ms_cmd_heredoc.c` — `unquoted_delimiter` re-implemented, `is_quote` deleted,
1 include added. Net: 6 lines shorter.

```diff
+#include "ms_token.h"
```

```diff
-static bool	is_quote(char c)
-{
-	return (c == '"' || c == '\'');
-}
-
-// returns NULL if the input delimter was not quoted
+// returns NULL if the input delimiter carried no quotes at all,
+// otherwise the delimiter with every quote removed
 static char	*unquoted_delimiter(char *delimiter)
 {
-	size_t	input_len;
+	char	*unquoted;

 	if (delimiter == NULL)
 		return (NULL);
-	input_len = ft_strlen(delimiter);
-	if (input_len > 2 && is_quote(delimiter[0])
-		&& delimiter[0] == delimiter[input_len - 1])
-		return (ms_substr(delimiter, 1, input_len - 2));
-	return (NULL);
+	unquoted = remove_quote(ms_strdup(delimiter));
+	if (ft_strlen(unquoted) != ft_strlen(delimiter))
+		return (unquoted);
+	return (ft_free(unquoted), NULL);
 }
```

**Why.** The old version only recognised a delimiter quoted *as a whole* — first character a quote,
last character the same quote. `<< lim''` and `<< "$US"E"R"` are quoted too, just not like that, so
they fell through to the "not quoted" branch: minishell kept expanding the body and never matched
the terminator line, swallowing the rest of the input.

Instead of adding more special cases, the delimiter now goes through `remove_quote()` — the same
quote-stripping the expander already uses on every other word, so the quote state machine is
written once. "Was it quoted?" then becomes "did stripping change its length?", which is true for
every form of quoting and false for a bare `EOF`.

`ms_strdup` first, because `remove_quote` frees what it is given and the caller's delimiter must
survive. The two call sites in `ms_gnl_heredoc` did not change: they already handled both the
"quoted → no expansion" and "unquoted → expand" branches.

`is_quote` became unused, and an unused static function is an error under `-Werror`, so it had to
go with it. That also drops `ms_cmd_heredoc.c` from 11 to 10 functions — still over the norm's
limit of 5, which is pre-existing and not something I touched.

**Effect:** both cases now match bash:

| case | delimiter | body expanded? |
|---|---|---|
| `1_redirs.sh:229` | `lim''` → `lim` | no (quoted) — `$USER` stays literal |
| `10_parsing_hell.sh:45` | `"$US"E"R"` → `$USER` | no (quoted), terminator now recognised |

---

## Verification

- `make` is clean under `-Wall -Wextra -Werror`.
- `norminette` passes on `ms_exec_builtins_unset.c`, `ms_exec_child.c` and `ms_exec_utils.c`.
  `ms_cmd_heredoc.c` still reports `TOO_MANY_FUNCS`, exactly as it did before these fixes (it has
  more than five functions since long before; the fix removed one of them).
- Each of the 58 cases in groups 1, 5 and 11 was re-run in an **empty directory** against the new
  binary and against bash: **56 match byte for byte, including the exit code**; the 2 listed under
  fix 1 remain.
- Full suite re-run (`mstest vm`, valgrind on every case): 941 cases, **841 passed**, 91 failing
  cases, **0 cases that were passing before now fail**, and **0 of the 941 cases leak**. The fast
  re-run without valgrind (`mstest m`) gives the identical 91, so the two agree.
- valgrind (`--leak-check=full`, project suppression file) was also run by hand on the paths these
  fixes touch — `unset A B C`, `cat << lim''`, `cat << "$US"E"R"`, `/bin/cats`, `.`, `./nope` — and
  reports no definitely/indirectly lost bytes. The `ms_strdup` added in fix 3 is freed by
  `remove_quote`, and its result by the existing `ft_free(unq_deli)` in `ms_gnl_heredoc`.

## What is left failing (91) — unchanged by design

| group | cases | why it stays |
|---|---|---|
| `$"..."` / `$'...'` | 31 | bash locale / ANSI-C quoting, not in the subject |
| word splitting | 17 | expansion does not split on whitespace, not in the subject |
| backslash escaping | 14 | `\` handling is excluded by the subject |
| junk files in the project dir | 7 | tester artifact — passes in a clean directory |
| env noise (`SHLVL`, `_`, locale) | 5 | comparing two different shells' environments |
| `~` | 5 | tilde expansion not implemented |
| `export` option-like names | 3 | exit 1 vs bash 2 |
| `unset TES;T`, `unset -TEST` | 2 | `;` separator and option parsing |
| `>\|` | 2 | bash-only redirection operator |
| `export` with no arguments | 1 | prints `export 'NAME=value'`, bash prints `declare -x` sorted |
| `export TEST+=100` | 1 | regression from the earlier branch work, listed in `test_out_c.md` |
| multi-line quoted string | 1 | regression from the earlier branch work, listed in `test_out_c.md` |
| `cd --` | 1 | `--` not treated as end-of-options |
| `2>` | 1 | fd-prefixed redirection not in the subject |
