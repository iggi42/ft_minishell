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
#include "ms_env.h"
#include "ms_signal.h"
#include <stdio.h>
#include <readline/readline.h>
#include "libft_merle.h"
#include "libft_str.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "ms_exit.h"

// the prompt is reset here, so the SIGINT has to be forgotten too:
// a heredoc typed on this same readline line is not interrupted by it
int	ms_rl_main_event_hook(void)
{
	int	sig;

	sig = ms_signal_consume();
	if (sig == SIGINT)
	{
		(void)write(STDIN_FILENO, "\n", 1);
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
	{
		(void)write(STDIN_FILENO, "\n", 1);
		rl_done = 1;
	}
	return (0);
}

char	*ms_repl_rl_wrapper(char *prompt, int (*ms_rl_hook)(void) )
{
	char	*line;

	rl_event_hook = ms_rl_hook;
	line = readline(prompt);
	if (!ft_m3_add(line))
	{
		free(line);
		ms_error_out(EXIT_FAILURE, NULL, errno);
	}
	return (line);
}
