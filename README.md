*This project has been created as part of the 42 curriculum by [fkruger](https://github.com/iggi42) and [stmuller](https://github.com/cuteKittenArri).*

# minishell

## Description

`minishell` is a small POSIX-style command interpreter written from scratch in C, as required
by the 42 *minishell* project. The goal is to rebuild the core of a shell such as `bash`: read
a line from the user, split it into tokens, expand variables and quotes, build a pipeline of
commands with their redirections, and then execute that pipeline with `fork`, `pipe`, `dup2`
and `execve` — while keeping the exit status, the environment and the terminal signals
behaving the way a real shell does.

The shell runs both **interactively** (with a `readline` prompt, line editing and history) and
**non-interactively**, reading commands from a pipe or a file, which makes it usable in scripts:

```console
$ ./minishell
minishell %> echo hello | tr a-z A-Z
HELLO
minishell %> exit
$ echo 'pwd' | ./minishell
/home/you/ft_minishell
```

Only the **mandatory** part of the subject is implemented: there are no logical operators
(`&&`, `||`), no command separator `;`, no subshells with parentheses, no wildcard expansion
and no `~` expansion.

### Feature list

| Area | What is supported |
|------|-------------------|
| Prompt | `readline`-based prompt with line editing and in-memory history; the prompt string can be overridden through `PS1` (and `PS2` for heredocs) |
| Quoting | single quotes (no interpretation at all) and double quotes (everything but `$` is literal), including quotes that come out of a variable's *value* |
| Expansion | `$VAR` (a name made of letters, digits and `_`, not starting with a digit) and `$?` for the last exit status; unset variables expand to nothing |
| Pipelines | `cmd1 \| cmd2 \| cmd3 …`, arbitrary length, every stage in its own process |
| Redirections | `<` input, `>` truncating output, `>>` appending output, `<<` heredoc (with expansion, or literal when the delimiter is quoted) |
| Builtins | `echo` (with `-n`), `cd` (no argument goes to `HOME`, `cd -` to `OLDPWD`, both `PWD` and `OLDPWD` are kept up to date), `pwd`, `export`, `unset`, `env`, `exit` |
| Execution | `PATH` lookup that honours empty entries, absolute and relative paths, `127` for *command not found*, `126` for a file that cannot be executed |
| Exit status | `$?` after builtins, external commands and signals (`128 + signo`), and as the shell's own exit code |
| Signals | `Ctrl-C` redraws a fresh prompt, `Ctrl-D` ends the shell, `Ctrl-\` leaves the shell itself alive but still reaches a running child; the same behaviour inside a heredoc |
| Resources | all file descriptors and child processes are tracked centrally and cleaned up, so the shell leaks neither memory nor fds |

## Instructions

### Requirements

* a C compiler (`cc`/`gcc`) and `make`
* the **GNU readline** library and its headers — on Debian/Ubuntu:
  `sudo apt install libreadline-dev`
* `libft` is **not** an external dependency: it lives in `libft/` inside this repository and is
  built automatically.

### Compilation

```console
$ make
```

This builds `libft/libft.a` first and then links the `minishell` binary in the repository root.
Objects are written to `bin/`. The usual 42 targets are available:

| Target | Effect |
|--------|--------|
| `make` / `make all` | build `minishell` |
| `make clean` | remove the object files (in `bin/`) and the dependency files |
| `make fclean` | `clean` plus the `minishell` binary and `libft.a` |
| `make re` | `fclean` followed by a full rebuild |
| `make dev` | generate the development helpers (`.gitignore`, `compile_flags.txt` for clangd) |

The project is compiled with `-Wall -Wextra -Werror`.

### Execution

```console
$ ./minishell
```

`minishell` takes no arguments; it refuses to start if it is given any. Type commands at the
prompt and leave with `exit` or `Ctrl-D`. Commands can also be piped in, in which case no
prompt is printed and the first syntax error aborts the run (exit status `2`), just like a
non-interactive `bash`:

```console
$ printf 'export GREETING=hi\necho $GREETING world\n' | ./minishell
hi world
```

## Usage examples

```console
minishell %> echo -n "no trailing newline"   # -n is honoured, also written as -nnn
no trailing newlineminishell %> cat < Makefile | grep SRCS | wc -l
21
minishell %> ls /does/not/exist
ls: cannot access '/does/not/exist': No such file or directory
minishell %> echo $?
2
minishell %> export NAME=42
minishell %> echo "hello $NAME"
hello 42
minishell %> cat << EOF
minishell_heredoc %> the shell level is $SHLVL
minishell_heredoc %> EOF
the shell level is 2
minishell %> cat << "EOF"
minishell_heredoc %> $HOME stays literal here
minishell_heredoc %> EOF
$HOME stays literal here
minishell %> echo one > out.txt
minishell %> echo two >> out.txt
minishell %> cat out.txt
one
two
minishell %> exit 42
$ echo $?
42
```

## Technical choices

The shell is a pipeline of four clearly separated stages, each in its own group of files under
`src/`:

1. **Tokenizer** (`ms_token.c`, `ms_token_utils.c`) turns the raw line into a linked list of
   tokens (`T_WORD`, `T_PIPE`, `T_IN`, `T_OUT`, `T_OUT_APPEND`, `T_HERE_DOC`) and reports
   syntax errors such as an unclosed quote or a redirection without a target.
2. **Expander** (`ms_expander_var.c`, `ms_expander_quotes.c`, `ms_expander_utils.c`) performs
   variable expansion and quote removal. Quote characters that arrive inside a variable's value
   are temporarily replaced by the markers `MS_HIDDEN_SQ`/`MS_HIDDEN_DQ`, so the quote-removal
   pass cannot mistake them for syntax.
3. **Parser** (`ms_parsing*.c`, `ms_cmd_new.c`, `ms_redi.c`) builds a NULL-terminated array of
   `t_ms_cmd`, each holding an `argv` and an array of `t_ms_redi` redirections. It returns a
   `t_ms_parse_res` that is either a command array or an error message, so the REPL has a
   single place to report failures.
4. **Executor** (`ms_exec*.c`) runs a single command in the parent when it is a non-forking
   builtin (`cd`, `exit`, `export`, `unset`), and otherwise forks. Pipelines are spawned stage
   by stage in `ms_exec_pipe.c`, and the exit status of the last stage becomes `$?`.

A few decisions worth pointing out:

* **The environment is a key/value store**, not a `char **`. `ms_env_*` wraps libft's `t_kv`;
  `environ` is imported at start-up and rebuilt on demand for `execve`. Special entries such as
  `?` live in the same store but are hidden from `env` and `export` output.
* **Two bookkeepers guard the resources.** `bw` (`src/bw_core.c`) remembers every open file
  descriptor and `kg` (`src/kg_core.c`, the "kindergarten") every child pid, so both the parent
  and a freshly forked child can drop everything they must not keep with a single call.
* **Allocation and syscalls go through `ms_safe_*`.** These thin wrappers abort the shell with a
  clean error instead of letting a failed `malloc`, `fork` or `pipe` propagate an unchecked
  `NULL` or `-1`, which keeps the rest of the code readable within the 25-line Norm limit.
* **Only one global variable exists**, `g_ms_signal` in `src/ms_signal_handler.c`, as the subject
  demands: the handler does nothing but store the signal number, and the REPL consumes it later
  at a safe point.
* Heredocs are collected *before* the pipeline starts (`ms_cmd_heredoc.c`) and can be
  interrupted with `Ctrl-C` without taking the shell down with them.
* The whole project is written against the **42 Norm** (`norm.pdf`, version 4.1) and compiles
  with `-Wall -Wextra -Werror`.

### Repository layout

```
inc/      public headers, one per module
src/      implementation (tokenizer, expander, parser, executor, builtins, env, signals)
libft/    our own C library (strings, arrays, key/value store, printf, get_next_line)
```

## Resources

Documentation and references used while building the shell:

* `man 3 readline`, `man 3 history` — the GNU Readline and History libraries
  ([official manual](https://tiswww.case.edu/php/chet/readline/rltop.html))
* `man 2 fork`, `man 2 pipe`, `man 2 dup2`, `man 2 execve`, `man 2 waitpid`, `man 2 open` —
  the syscalls the whole executor is built on
* `man 2 sigaction`, `man 7 signal`, `man 7 signal-safety` — signal handling and what is
  allowed inside a handler
* [POSIX Shell Command Language (IEEE Std 1003.1)](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
  — the reference for tokenization, quoting, expansion order and exit statuses
* [The GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) —
  the concrete behaviour we compared against, especially for `echo -n`, `cd -`, `export`
  output and heredoc delimiters
* [Bash source code](https://git.savannah.gnu.org/cgit/bash.git) — for corner cases where the
  manual is ambiguous
* `bash` itself, run side by side with `minishell`: the reference implementation is the final
  arbiter for every disputed case

### Use of AI

*To be filled in by the authors.*

### 👤 Author
- [cuteKittenArri](https://github.com/cuteKittenArri)
- [iggi42](https://github.com/iggi42)

<img src="mage.gif" alt="arri" style="max-width: 180px;">
