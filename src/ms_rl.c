/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_rl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:01:19 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 12:01:20 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"
#include "libft_mem.h"
#include "libft_merle.h"
#include "libft_str.h"
#include "ms_env.h"
#include "ms_exit.h"
#include "ms_signal.h"
#include <errno.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// the prompt is reset here, so the SIGINT has to be forgotten too:
// a heredoc typed on this same readline line is not interrupted by it
int	ms_rl_main_event_hook(void)
{
	int	sig;

	sig = ms_signal_consume();
	if (sig == SIGINT)
	{
		(void)write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ms_signal_listen(0);
	}
	return (0);
}

int	ms_rl_heredoc_event_hook(void)
{
	int	sig;

	sig = ms_signal_consume();
	if (sig == SIGINT)
		rl_done = 1;
	return (0);
}

char	*ms_repl_rl_wrapper(char *prompt, int (*ms_rl_hook)(void))
{
	char	*line;

	rl_event_hook = ms_rl_hook;
	if (ms_signal_consume() == SIGINT)
	{
		write(1, "\n", 1);
		ms_signal_listen(0);
	}
	line = readline(prompt);
	if (line != NULL && !ft_m3_add(line))
	{
		free(line);
		ms_error_out(EXIT_FAILURE, MS_MEM_ERR, errno);
	}
	return (line);
}
