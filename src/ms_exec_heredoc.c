/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:24:39 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/23 15:24:40 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bw.h"
#include "ms_utils.h"
#include "ms_exec_utils.h"
#include <errno.h>
#include <libft_io.h>
#include <libft_mem.h>
#include <libft_ll.h>
#include <libft_arr.h>
#include <libft_str.h>
#include <unistd.h>

static void	here_doc_write(int fd, char **s)
{
	ms_dup2(fd, STDOUT_FILENO);
	ft_bw_cleanup();
	while (*s)
	{
		if (0 > ft_write(STDOUT_FILENO, *s, ft_strlen(*s)))
			ms_error_out(EXIT_FAILURE, "heredoc write failure", errno);
		s++;
	}
	ms_exit(EXIT_SUCCESS);
}

int	write_in_fork(char **s, pid_t *writer)
{
	int	my_pipe[2];

	ms_pipe(my_pipe);
	*writer = ms_fork();
	if (*writer == 0)
		(ms_close(my_pipe[R]), here_doc_write(my_pipe[W], s));
	ms_close(my_pipe[W]);
	return (my_pipe[R]);
}

// 2 try
char	**read_here_doc2(char *(*gnl)(void), char *delimiter)
{
	t_list	*result;
	t_arr	*return_val;
	char	*line;
	char	*deli_nl;

	result = NULL;
	deli_nl = ft_strf("%s\n", delimiter);
	line = gnl();
	while (deli_nl && line)
	{
		if (!ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1)
			|| !ft_strncmp(deli_nl, line, ft_strlen(deli_nl) + 1))
			break ;
		ft_lstadd_back(&result, ft_lstnew(line));
		line = gnl();
	}
	ft_free(deli_nl);
	return_val = ft_lst2arr(result);
	ft_lstclear(&result, ft_void);
	return ((char **)return_val);
}

static char	*stdin_gnl(void)
{
	return (ft_gnl(STDIN_FILENO));
}

int	fill_here_doc(char *delimiter, pid_t *writer)
{
	char	**lines;

	lines = read_here_doc2(stdin_gnl, delimiter);
	return (write_in_fork(lines, writer));
}
