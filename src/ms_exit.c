#include "ms_utils.h"
#include <libft_io.h>
#include <libft_merle.h>
#include <libft_str.h>
#include <unistd.h>

void	*ms_exit_if(void *cond, const char *error_msg)
{
	if (cond)
		return (cond);
	ft_putendl_fd((char *)error_msg, STDERR_FILENO);
	ft_m3_cleanup();
	exit(EXIT_FAILURE);
	return (NULL);
}

void	*ms_protect(void *cond)
{
	return (ms_exit_if(cond, MS_MEM_ERR));
}
