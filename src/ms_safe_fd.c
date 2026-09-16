// This needs to have all the protected calls that deal with fds in here, open,
// 	close, dup, pipe, etc

#include "bw.h"
#include "libft_io.h"
#include "ms_exit.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	ms_open(char *path, int flags)
{
	int	fd;

	errno = 0;
	fd = open(path, flags, 0644);
	if (fd < 0)
		return (fd);
	return (ft_bw_add(fd), fd);
}

void	ms_close(int fd)
{
	if (ft_bw_rm(fd))
	{
		errno = 0;
		close(fd);
		if (errno != 0)
			ms_error_out(EXIT_FAILURE, NULL, errno);
	}
}

int ms_dup(int from)
{
	int new_fd;

	// ft_printf_fd(STDERR_FILENO, "ms_dup(%d)\n", from);
	errno = 0;
	new_fd = dup(from);
	if (new_fd >= 0)
		return (ft_bw_add(new_fd), new_fd);
	ms_error_out(EXIT_FAILURE, NULL, errno);
	return -1;
}

void	ms_dup2(int from, int to)
{
	errno = 0;
	if (dup2(from, to) == to)
	{
		// ft_printf_fd(STDERR_FILENO, "ms_dup2(%d, %d)\n", from, to);
		return (ft_bw_add(to));
	}
	ms_error_out(EXIT_FAILURE, NULL, errno);
}

int	*ms_pipe(int *new_pipe)
{
	errno = 0;
	if (pipe(new_pipe) != 0)
		return (ms_error_out(EXIT_FAILURE, NULL, errno), NULL);
	ft_bw_add(new_pipe[0]);
	ft_bw_add(new_pipe[1]);
	return (new_pipe);
}
