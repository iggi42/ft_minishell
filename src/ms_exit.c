#include "ms_exit.h"
#include "bw.h"
#include "ms_repl.h"
#include "kg.h"
#include <libft_io.h>
#include <libft_merle.h>
#include <unistd.h>
#include <string.h>

static void close_stdenv(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	ms_exit(int exit_code)
{
	ms_repl_history_clear();
	ft_bw_cleanup();
	close_stdenv();
	kg_cleanup(true);
	ft_m3_cleanup();
	exit(exit_code);
}

void ms_complain(char *msg, int error_code)
{
	if (msg != NULL)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		if (error_code != 0)
			ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error_code != 0)
		ft_putstr_fd(strerror(error_code), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	ms_error_out(int exit_code, char *msg, int error_code)
{
	ms_complain(msg, error_code);
	ms_exit(exit_code);
}

void	*ms_exit_if(void *cond, char *error_msg)
{
	if (cond)
		return (cond);
	if(error_msg)
		ft_putendl_fd((char *)error_msg, STDERR_FILENO);
	ms_exit(EXIT_FAILURE);
	return (NULL);
}

