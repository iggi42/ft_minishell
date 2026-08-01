/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:03:20 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/19 15:03:21 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <sys/wait.h>

static int	get_exit_code(int res)
{
	if (WIFEXITED(res))
		return (WEXITSTATUS(res));
	if (WIFSIGNALED(res))
		return (128 + WTERMSIG(res));
	return (res);
}

int	ft_wait(pid_t pid)
{
	int		res;
	pid_t	sig_pid;

	res = 0;
	while (true)
	{
		sig_pid = waitpid(pid, &res, 0);
		if (sig_pid == pid)
			return (get_exit_code(res));
	}
}
