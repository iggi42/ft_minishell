#include "bw.h"
#include "ms_cmd_t.h"
#include "ms_env.h"
#include "ms_exec.h"
#include "ms_exec_builtins.h"
#include "ms_exec_utils.h"
#include "ms_exit.h"
#include "ms_redi.h"
#include "ms_safe.h"
#include <errno.h>
#include <libft_arr.h>
#include <libft_str.h>
#include <unistd.h>

void	ms_stdenv_apply(int stdenv[2])
{
	ms_dup2(stdenv[R], STDIN_FILENO);
	ms_dup2(stdenv[W], STDOUT_FILENO);
}

static void	ms_execve(char *path, char **argv)
{
	execve(path, argv, ms_env_environ_export());
	ms_error_out(EXIT_NO_EXEC_PERM, "[ missing ]", 0);
}

static void	ms_exec_do_cmd(char **argv)
{
	char		*path;
	ms_builtin	bilt;

	if (argv[0] == NULL)
		ms_exit(EXIT_SUCCESS);
	path = ms_find_exec_file(argv[0]);
	if (path)
		ms_execve(path, argv);
	bilt = ms_builtin_get(argv[0]);
	if (bilt)
		ms_exit(bilt(argv));
	ms_error_out(EXIT_CMD_NOT_FOUND, ft_strf("%s: command not found", argv[0]),
		0);
}

void	ms_exec_child(t_ms_cmd *cmd, int stdenv[2])
{
	ms_stdenv_apply(stdenv);
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))ms_redi_apply);
	ft_bw_cleanup();
	ms_exec_do_cmd(cmd->argv);
}
