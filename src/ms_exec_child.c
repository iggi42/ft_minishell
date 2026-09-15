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

void	ms_exec_child(t_ms_cmd *cmd, int stdenv[2])
{
	char		*path;
	ms_builtin	built_in;

	ms_stdenv_apply(stdenv);
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))ms_redi_apply);
	if (cmd->argv[0] == NULL)
		ms_exit(EXIT_SUCCESS);
	built_in = ms_get_builtin(cmd->argv[0]);
	path = ms_find_exec_file(cmd->argv[0]);
	ft_bw_cleanup();
	if (built_in != NULL)
		ms_exit(built_in(cmd->argv));
	else
		execve(path, cmd->argv, ms_env_environ_export());
	if (path == NULL || access(path, F_OK))
	{
		path = ft_strf("%s: command not found", cmd->argv[0]);
		ms_error_out(EXIT_CMD_NOT_FOUND, path, 0);
	}
	ms_error_out(EXIT_NO_EXEC_PERM, path, errno);
}
