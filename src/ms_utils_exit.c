#include "ms_utils.h"
#include "bw.h"
#include <libft_io.h>
#include <libft_merle.h>
#include <unistd.h>
#include <string.h>
#include <readline/history.h>

void	ms_exit(int exit_code)
{
	clear_history();
	ft_bw_cleanup();
	ft_m3_cleanup();
	exit(exit_code);
}

void	ms_error_out(int exit_code, char *msg, int error_code)
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
	ms_exit(exit_code);
}

void	*ms_exit_if(void *cond, char *error_msg)
{
	if (cond)
		return (cond);
	ft_putendl_fd((char *)error_msg, STDERR_FILENO);
	ms_exit(EXIT_FAILURE);
	return (NULL);
}

void	*ms_protect(void *cond)
{
	return (ms_exit_if(cond, MS_MEM_ERR));
}
