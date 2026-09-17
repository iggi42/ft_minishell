# minishell — minimal-patch plan for bugs.txt (+ 4 approved extras)

Nothing has been applied. Every fix below is the **smallest change that actually fixes the
bug**: no function is deleted, no file is rewritten, no signature changes, no new struct, no
new field in `t_token`. Two functions are added in one new file, everything else is a patch
of one to four lines.

Budget: **1 new file (2 functions), 1 new function in `ms_exec_utils.c`, 1 new function in
`ms_token.c`, 1 new function in `ms_atoi.c`, ~30 changed/added lines. One line deleted.**

| Fix | Files | Size |
|-----|-------|------|
| 1 `$NOVAR` | `ms_expander_var.c`, `ms_exec.c` | 2 conditions, 1 line moved |
| 2 PATH `:` | `ms_exec_utils.c` | 1 line changed + 1 new function |
| 3 value quotes | `ms_expander_var.c`, new `ms_expander_quotes.c`, `Makefile` | 6 lines + 2 new functions |
| 4 signals | `ms_signal.c`, `ms_signal_handler.c`, `ms_rl.c`, `ms_cmd_heredoc.c`, `ms_exec.c` | 7 lines, 1 deleted |
| `>>` at col 0 | `ms_token.c` | **1 character** |
| unclosed quote | `ms_token.c`, `ms_token.h`, `ms_parsing.c` | 3 lines + 1 new function |
| `export` | `ms_exec_builtins_export.c` | 2 lines |
| `exit` | `ms_exec_builtins_exit.c`, `ms_atoi.c`, `ms_utils.h` | 9 lines + 1 new function |

Norm (norm.pdf v4.1) was checked for every patched function: all stay ≤25 lines, ≤5
variables, ≤4 parameters, and no file goes over 5 function definitions. Where a function is
already at the 25-line limit the patch is designed to fit anyway — that is noted inline.

---

## Fix 1 — `$NOVAR` prints "command not found"

`ms_expand()` skips the **first** token of the line: the `prev_token != NULL` guard was meant
to protect a heredoc delimiter, but it also skips the command word, so `$NOVAR`, `"ls"` and
`$HOME/bin/x` reach execve verbatim. (Only the very first word of the line is affected — the
word after a `|` has the pipe token as `prev_token`, so it was already expanded.)

**`src/ms_expander_var.c:109` and `:120` — invert the guard in both loops:**

```c
-		if (current->kind == T_WORD && prev_token != NULL
-			&& prev_token->kind != T_HERE_DOC)
+		if (current->kind == T_WORD && (prev_token == NULL
+				|| prev_token->kind != T_HERE_DOC))
			ms_expand_var(&current->value, true);
```

```c
-		if (current->kind == T_WORD && prev_token != NULL
-			&& prev_token->kind != T_HERE_DOC)
+		if (current->kind == T_WORD && (prev_token == NULL
+				|| prev_token->kind != T_HERE_DOC))
			current->value = remove_quote(current->value);
```

That is the whole fix. A word that expands to nothing is already dropped by
`del_empty_token`, `build_cmd_arr` already produces an empty array for no tokens, and
`ms_exec` already returns early on it.

**`src/ms_exec.c:25-27` — one line moved**, so an empty line leaves `$? = 0` like bash:

```c
-	if (*run_me == NULL)
-		return (0);
 	ms_env_set_status(0);
+	if (*run_me == NULL)
+		return (0);
```

---

## Fix 2 — an empty PATH entry must mean the current directory

`ms_search_path()` already has the right logic: `default_str(paths[i], ".")` at
`src/ms_exec_utils.c:32` turns an empty entry into the cwd. It is dead code only because
`ft_split` throws empty fields away (`libft/src/str/ft_split.c:65`, `word_l > 0`). So do not
touch the search loop — give it a splitter that keeps empty fields.

**`src/ms_exec_utils.c:27` — one changed line:**

```c
-	paths = ms_protect(ft_split(ms_env_get("PATH", "."), ':'));
+	paths = ms_split_path(ms_env_get("PATH", "."));
```

`ms_search_path` is exactly at the 25-line norm limit, which is why the new call has to be a
one-for-one replacement and not two lines.

**New function above it in the same file** (the file goes from 3 to 4 functions):

```c
// splits a PATH like string on ':' but keeps the empty entries,
// so ":/bin" stays two entries and the current dir keeps its position
static char	**ms_split_path(char *path)
{
	char	**result;
	size_t	count;
	size_t	i;
	char	*sep;

	count = 1;
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	result = (char **)ms_protect(ft_arr_new(count));
	i = 0;
	while (i < count)
	{
		sep = ft_strchr(path, ':');
		if (sep == NULL)
			sep = path + ft_strlen(path);
		result[i] = ms_substr(path, 0, sep - path);
		path = sep + 1;
		i++;
	}
	return (result);
}
```

25 lines, 4 variables, no new includes (`libft_arr.h`, `libft_str.h`, `ms_safe.h`,
`ms_exit.h` are all already included). The entries are `ms_substr` allocations, so the
existing `ft_arr_each((t_arr)paths, ft_free)` cleanup in `ms_search_path` still fits.

Result: `:/usr/bin` → cwd first, `/usr/bin::/bin` → cwd in the middle, `/usr/bin:` → cwd
last, `PATH=` → cwd only.

---

## Fix 3 — quotes that come out of a variable value get eaten

`echo $VAR` with `VAR='something'` prints `something`, because quote removal is a second pass
that runs over the **already expanded** string (`src/ms_expander_var.c:133`).

The minimal way to keep both passes exactly as they are is to make the value's quote
characters invisible to pass 2: hide them as two control bytes while the value is spliced in,
and bring them back after `remove_quote` has run. Pass 2, `del_empty_token`, the token type
and the heredoc path all stay untouched — and because `del_empty_token` still runs *before*
quote removal, `echo "" x` keeps printing ` x` (an empty quoted argument stays an argument).

**New file `src/ms_expander_quotes.c`** (generate the 42 header with `:Stdheader`):

```c
#include "ms_safe.h"
#include "ms_token.h"

// hides the quote characters of a variable value, so that the quote
// removal pass does not eat quotes that the user never typed
char	*ms_quote_hide(char *value)
{
	char	*result;
	size_t	i;

	result = ms_strdup(value);
	i = 0;
	while (result[i] != '\0')
	{
		if (result[i] == '\'')
			result[i] = MS_HIDDEN_SQ;
		else if (result[i] == '\"')
			result[i] = MS_HIDDEN_DQ;
		i++;
	}
	return (result);
}

// brings the hidden quote characters back, once quote removal is done
char	*ms_quote_show(char *str)
{
	size_t	i;

	i = 0;
	while (str != NULL && str[i] != '\0')
	{
		if (str[i] == MS_HIDDEN_SQ)
			str[i] = '\'';
		else if (str[i] == MS_HIDDEN_DQ)
			str[i] = '\"';
		i++;
	}
	return (str);
}
```

**`inc/ms_token.h` — 4 added lines**, next to the existing `remove_quote` declaration:

```c
# define MS_HIDDEN_SQ 1
# define MS_HIDDEN_DQ 2

char				*ms_quote_hide(char *value);
char				*ms_quote_show(char *str);
```

**`Makefile:22` — one changed line:**

```make
-SRCS += ms_expander_var.c ms_expander_utils.c
+SRCS += ms_expander_var.c ms_expander_utils.c ms_expander_quotes.c
```

**`src/ms_expander_var.c:48` — `ms_exp_var_sect` takes the mode it already has one frame up,
and hides the value's quotes only when there will be a quote removal pass** (heredoc lines
are expanded with `quotes == false` and never quote-removed, so they must not be hidden):

```c
-static t_iol_el	*ms_exp_var_sect(char *s_dollar, size_t *consumed)
+static t_iol_el	*ms_exp_var_sect(char *s_dollar, size_t *consumed, bool quotes)
 {
 	...
 	else
 	{
 		var_name = ms_substr(s_dollar, 1, *consumed);
 		result->buffer = ms_env_get(var_name, "");
+		if (quotes)
+		{
+			result->buffer = ms_quote_hide(result->buffer);
+			result->free = ft_iol_free_always;
+		}
 		result->size = ft_strlen(result->buffer);
 		ft_free(var_name);
 	}
```

24 lines after the patch, still under the limit. `ft_iol_free_always` (libft) frees
`el->buffer`, so `ft_iol_del` at the end of `ms_expand_var` releases the hidden copy — no
leak, and the borrowed-pointer case (`quotes == false`) keeps `free == NULL` as today.

**`src/ms_expander_var.c:79` — pass the mode through (one changed line):**

```c
 	if (*s == '$')
-		result = ms_exp_var_sect(s, consumed);
+		result = ms_exp_var_sect(s, consumed, quotes);
```

**`src/ms_expander_var.c:133` — unhide right after quote removal (one changed line):**

```c
-			current->value = remove_quote(current->value);
+			current->value = ms_quote_show(remove_quote(current->value));
```

Worked example, `VAR='something'`:

| step | `echo $VAR` | `echo "$VAR"` | `echo "'$VAR'"` |
|------|-------------|---------------|-----------------|
| after expansion | `\x01something\x01` | `"\x01something\x01"` | `"'\x01something\x01'"` |
| after `remove_quote` | unchanged | `\x01something\x01` | `'\x01something\x01'` |
| after `ms_quote_show` | `'something'` | `'something'` | `''something''` |

which is what bash prints in all three cases.

Trade-off: bytes `\x01` / `\x02` in a value would come back out as quotes. They cannot be
typed into a shell line through readline, and nothing in the codebase produces them.

---

## Fix 4 — ctrl+C, then a heredoc, closes instantly

The repro: ctrl+C at the prompt is handled **inside** the same `readline()` call
(`ms_rl_main_event_hook` clears the line and redraws the prompt without returning), so
`last_signal` is still `SIGINT` when you then type `cat << EOF` on that same line, and the
first statement of `ms_gnl_heredoc` (`src/ms_cmd_heredoc.c:75`) bails out. Second path to the
same symptom: a SIGINT that arrives while a command runs is never consumed, so the next
readline event hook re-arms `last_signal` at the fresh prompt.

**`src/ms_rl.c:26` — forget the SIGINT once the prompt has been reset (one added line):**

```c
 	if (sig == SIGINT)
 	{
 		(void)write(STDIN_FILENO, "\n", 1);
 		rl_replace_line("", 0);
 		rl_on_new_line();
 		rl_redisplay();
+		ms_signal_listen(0);
 	}
```

`ms_signal_listen(0)` only clears `last_signal`; it does not touch `$?` when `sig == 0`, so
`$?` correctly stays 130. `ms_signal_last()` is read **only** by `ms_gnl_heredoc` (grep
confirmed), so nothing else can notice.

**`src/ms_signal.c:20` — make that reset also drop an unconsumed signal (two added lines):**

```c
 void	ms_signal_listen(int sig)
 {
+	if (sig == 0)
+		ms_signal_consume();
 	*last_signal_store() = sig;
 	if (sig != 0)
 		ms_env_set_status(128 + sig);
 }
```

`ms_signal_consume()` triggers the stored handler, which for SIGINT is `ms_signal_listen`
itself — recursion depth 1, `sig != 0` on the inner call, so it sets `$? = 130` and returns;
the outer call then clears `last_signal`. `ms_repl` already calls `ms_signal_listen(0)` at the
top of every loop, so the ctrl+C you pressed during `sleep 10` is now drained there instead
of surfacing at the next prompt. **No change needed in `ms_repl.c`** (that function is exactly
at the 25-line limit anyway).

**`src/ms_cmd_heredoc.c:78` — delete one line:**

```c
-	if (ms_env_get_status() != 0)
-		return (NULL);
```

Keying the heredoc on `$?` means *any* non-zero status kills it (ctrl+\ sets 131, for
instance). The two `ms_signal_last() == SIGINT` checks around it already do the real job, and
ctrl+C during the heredoc still ends the read through `rl_done` in
`ms_rl_heredoc_event_hook`. (`#include "ms_env.h"` becomes unused in that file — removing it
is optional.)

**`src/ms_exec.c:29` — an interrupted heredoc throws the command away (two added lines):**

```c
 	ft_arr_each((t_arr)run_me, (void (*)(t_arr_el))ms_heredocs_prepare);
-	if (*(run_me + 1) == NULL)
+	if (ms_signal_last() == SIGINT)
+		result = 128 + SIGINT;
+	else if (*(run_me + 1) == NULL)
 		result = ms_exec_cmd(*run_me);
 	else
 		result = ms_exec_pipe(run_me);
```

The existing `ft_arr_each(..., ms_heredoc_cleanup)` and `ms_env_set_status(result)` lines
below still run, so the partial lines are freed, the writer child is reaped and `$?` becomes
130 — bash's behaviour, and today's "run the command with half the heredoc" goes away. Needs
`#include "ms_signal.h"` and `<signal.h>` (two added include lines).

**`src/ms_signal_handler.c:16` — the handler table is one element long.** `t_byte` is
`unsigned char`, so `store[sizeof(t_byte)]` is `store[1]`, and it is indexed with the signal
number: `store[2]`, `store[3]`, `store[13]`, plus `store[255]` from
`ms_signal_init`'s `ms_signal_set_handler(-1, NULL)`. Every registration writes out of bounds.

```c
-	static t_ms_sig_handler	store[sizeof(t_byte)];
+	static t_ms_sig_handler	store[MS_SIG_SLOTS];
```

with one added line in `inc/ms_signal.h`:

```c
# define MS_SIG_SLOTS 256
```

A `t_byte` index can only be 0-255, so every call is now in range. One more added line makes
the `-1` init call stop calling `signal(-1, SIG_DFL)` as well:

```c
 	if (sig < 0)
 	{
 		sigemptyset(&s_sig.sa_mask);
 		s_sig.sa_handler = ms_real_sh;
 		s_sig.sa_flags = 0;
+		return ;
 	}
```

**Optional (one line)** — `ms_heredoc_cleanup` waits for the writer child; if more than 64 KB
had been typed into the heredoc before ctrl+C, the writer would still be blocked on the full
pipe. Closing the read end first removes that theoretical hang:

```c
 void	ms_heredoc_cleanup(t_ms_cmd *cmd)
 {
 	if (cmd == NULL)
 		return ;
+	ms_redi_turnoff(cmd->active_heredoc.source_redi);
 	ms_heredoc_cleanup_ready(&cmd->active_heredoc);
```

Safe on the normal path too: `ms_close` only closes what the `bw` registry still holds, and
`ft_bw_cleanup` has already emptied it.

**Optional (one line)** — bash leaves the cursor on a new line after an interrupted heredoc:

```c
 	if (sig == SIGINT)
+	{
+		(void)write(STDIN_FILENO, "\n", 1);
 		rl_done = 1;
+	}
```

---

## Extra 1 — `>>` at the start of a line truncates (one character)

`if (str[i] == '>' && str[i + 1] == '>' && i++)` — `i++` yields the **old** value, so at
`i == 0` the condition is false while `i` has already been incremented: `>>out` at column 0
falls through to the `T_OUT` branch and truncates the file. `++i` yields the new value, which
is always ≥ 1:

```c
-	if (str[i] == '>' && str[i + 1] == '>' && i++)
+	if (str[i] == '>' && str[i + 1] == '>' && ++i)
 		type = T_OUT_APPEND;
```

`len` stays 1 and `i` now points at the second `>`, so `ms_substr(str, i, len)` and
`return (i + len)` both still land correctly — `src/ms_token.c` needs nothing else.

---

## Extra 2 — an unclosed quote silently does nothing

`handle_arg` returns -1 → `ms_tokenize` returns NULL → indistinguishable from an empty line,
so `echo "hi` succeeds and runs nothing. Rather than change `ms_tokenize`'s signature and its
caller, tell the two cases apart in `ms_parse`: a NULL token list from a line that is not
blank can only mean an unclosed quote.

**`src/ms_token.c` — one new function** (the file goes to 5, its limit):

```c
// tells an empty line apart from a line that failed to tokenize
int	ms_line_is_blank(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	return (input[i] == '\0');
}
```

**`inc/ms_token.h` — two added lines:**

```c
# define ERR_MSG_UNCLOSED "syntax error: unexpected end of file"
...
int					ms_line_is_blank(char *input);
```

**`src/ms_parsing.c:115` — one line becomes four** (function goes 19 → 22 lines):

```c
-	result->source.error_msg = ms_syntax_check(tkns);
+	if (tkns == NULL && !ms_line_is_blank(input))
+		result->source.error_msg = ms_strdup(ERR_MSG_UNCLOSED);
+	else
+		result->source.error_msg = ms_syntax_check(tkns);
```

`ms_repl` already prints `minishell: <msg>`, sets `$? = 2` interactively and exits 2 from a
script.

---

## Extra 3 — `export` identifiers (two lines)

`import_var` accepts anything whose *prefix* is a valid name, so `export FOO` and
`export FOO-BAR=1` both fall into the `ms_strdup("")` branch and create a variable with an
**empty name** (`env` then prints a bare `=`). `export ?=x` is accepted too and overwrites the
entry behind `$?`.

**`src/ms_exec_builtins_export.c:22` — widen the rejection (one line becomes three):**

```c
-	if (var_name_len == 0)
+	if (var_name_len == 0 || arg[0] == '?'
+		|| (arg[var_name_len] != '=' && arg[var_name_len] != '\0'))
 	{
```

**`src/ms_exec_builtins_export.c:33` — a bare `NAME` keeps its own name (one line):**

```c
 	if (arg[var_name_len] == '=')
 		var_name = ms_substr(arg, 0, var_name_len);
 	else
-		var_name = ms_strdup("");
+		var_name = ms_substr(arg, 0, var_name_len);
```

The existing `if (arg[var_name_len] == '\0') ms_env_set(var_name, "")` branch below then does
the right thing: `export FOO` stores `FOO=""` instead of `""=""`. Function ends at 24 lines,
just inside the limit.

Deviation kept on purpose: bash lists `export FOO` as `declare -x FOO` and hides it from
`env`, while this stores `FOO=`. Matching bash exactly needs an early `return (0)`, which
pushes the function over 25 lines unless the dead `print_exports` (line 67, never called) is
deleted to free a slot for an error-message helper. Say the word and it is two more lines.

---

## Extra 4 — `exit`

`exit abc` exits 2 **silently** (`ms_atoi` returns 2 for garbage, indistinguishable from a
real `exit 2`) and `exit 1 2` returns 2 with no message.

**`src/ms_atoi.c` — one new function** (file goes 3 → 4), reusing the validator that is
already there:

```c
bool	ms_atoi_valid(char *str)
{
	return (!invalid(str));
}
```

**`inc/ms_utils.h` — one added line:** `bool	ms_atoi_valid(char *str);`

**`src/ms_exec_builtins_exit.c` — the builtin grows from 14 to 23 lines:**

```c
 t_byte	ms_exec_builtin_exit(char **argv)
 {
 	t_byte	exit_code;
 	size_t	argc;
+	char	*msg;

 	argc = ft_arr_len((t_arr)argv);
-	if (argc > 2)
-		return (2);
+	if (isatty(STDIN_FILENO))
+		ft_putendl_fd("exit", STDERR_FILENO);
+	if (argv[1] != NULL && !ms_atoi_valid(argv[1]))
+	{
+		msg = ms_protect(ft_strf("minishell: exit: %s: "
+					"numeric argument required", argv[1]));
+		ms_complain(msg, 0);
+		ft_free(msg);
+		ms_exit(2);
+	}
+	if (argc > 2)
+		return (ms_complain("minishell: exit: too many arguments", 0), 1);
 	if (argv[0] == NULL)
 		ms_exit(EXIT_FAILURE);
```

The rest of the function is untouched. Order matches bash: `exit` prints `exit` when
interactive, `exit abc def` reports the numeric argument and exits 2, `exit 1 2` reports too
many arguments and **keeps the shell alive** with `$? = 1`. Added includes: `<unistd.h>`,
`libft_io.h`, `libft_mem.h`.

---

## Files touched

**New:** `src/ms_expander_quotes.c`.
**One line in the Makefile** (`SRCS +=` for that file).
**Patched:** `inc/ms_token.h`, `inc/ms_signal.h`, `inc/ms_utils.h`,
`src/ms_expander_var.c`, `src/ms_exec.c`, `src/ms_exec_utils.c`, `src/ms_token.c`,
`src/ms_parsing.c`, `src/ms_signal.c`, `src/ms_signal_handler.c`, `src/ms_rl.c`,
`src/ms_cmd_heredoc.c`, `src/ms_atoi.c`, `src/ms_exec_builtins_export.c`,
`src/ms_exec_builtins_exit.c`.

Untouched on purpose: `ms_expander_utils.c` (`remove_quote` and friends stay exactly as they
are), `ms_parsing_utils.c` (`alloc_cmd_array` / `count_cmd_elements` are dead but harmless),
`ms_exec_builtins_export.c`'s `print_exports`, `ms_token_utils.c`, `ms_cmd_*`, `ms_redi*`,
`ms_env_*`, `bw_core.c`, `kg_core.c`, `ms_repl.c`.

---

## Verification

```sh
make re
norminette src/ms_expander_quotes.c src/ms_expander_var.c src/ms_exec.c \
	src/ms_exec_utils.c src/ms_token.c src/ms_parsing.c src/ms_signal.c \
	src/ms_signal_handler.c src/ms_rl.c src/ms_cmd_heredoc.c src/ms_atoi.c \
	src/ms_exec_builtins_export.c src/ms_exec_builtins_exit.c \
	inc/ms_token.h inc/ms_signal.h inc/ms_utils.h
```

Compare against bash:

1. `$NOVAR` → nothing, `echo $?` → `0`; `"ls"` and `'ls'` run `ls`; `$NOVAR > out` still
   creates `out`. Regressions to re-check: `echo ""` → empty line; `echo "" x` → ` x`;
   `echo a"b"c` → `abc`; `echo "it's"`; `echo '"q"'`; `cat << $NOVAR` keeps the delimiter
   literal; `echo hi | cat` still fine.
2. `export PATH=":$PATH"` with `touch tst && chmod +x tst` → `tst` runs `./tst`;
   `PATH="/usr/bin::/bin"` → found in the middle; `PATH=` → cwd only; non-executable match →
   126, nothing found → 127.
3. `export VAR="'something'"` → `echo $VAR` and `echo "$VAR"` → `'something'`;
   `echo "'$VAR'"` → `''something''`; `VAR='a"b'; echo $VAR` → `a"b`; `env | grep VAR`
   unchanged; heredoc `cat << EOF` with `$VAR` inside → `'something'`, quotes intact.
4. ctrl+C at the prompt, then `cat << EOF` on the same line → heredoc reads normally; ctrl+C
   inside a heredoc → nothing runs, `echo $?` → `130`; `sleep 5` + ctrl+C then a heredoc →
   works, no stray blank line; several ctrl+C in a row then a heredoc → works;
   `<< "EOF"` still unexpanded.
5. Extras: `>>out echo hi` appends; `echo "hi` → `minishell: syntax error: unexpected end of
   file`, `$? = 2`; `export FOO` then `env | grep '^='` → nothing; `export 1BAD`,
   `export A-B=1`, `export ?=x` → not a valid identifier, `$? = 1`; `exit abc` → message +
   exit 2; `exit 1 2` → message, shell alive, `$? = 1`.

Then `valgrind --leak-check=full --show-leak-kinds=all ./minishell < script.txt` over the
same cases — in particular fix 3, which is the only one that adds an allocation
(`ms_quote_hide`, freed by `ft_iol_free_always` through `ft_iol_del`).

`make test` is not usable: `TESTS` lists `test/env_test.c` and `test/token_test.c`, but there
is no `test/` directory in the repo.

---

## Known edge cases these minimal fixes do **not** address

- `ms_expander_next_el` resets its quote state at every `$`, so `"$A'$B'"` does not expand
  `$B`. Pre-existing, unchanged, and it would need the expander pass rewritten.
- `ms_exec_maybe_run_builtin` (`src/ms_exec_cmd.c:24-28`) calls `ms_builtin_get_nofrk` and two
  `ms_dup`s before the `argv[0] == NULL` check. Harmless (`ft_str_eq` is NULL-safe,
  `ft_bw_cleanup` reclaims the dups).
- ctrl+\ at the prompt sets `$? = 131`; bash leaves `$?` alone. Self-heals on the next command.
- `export` without arguments prints `export 'NAME=value'`, unsorted; bash prints
  `declare -x NAME="value"` sorted.
