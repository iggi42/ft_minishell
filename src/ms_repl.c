/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_repl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:51:55 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 18:51:58 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"
#include "libft_merle.h"
#include "ms_env.h"
#include "ms_exec.h"
#include "ms_exit.h"
#include "ms_signal.h"
#include "ms_parsing.h"
#include "ms_repl.h"
#include <errno.h>
#include <libft_char.h>
#include <libft_mem.h>
#include <unistd.h>

static char	*ms_cut_nl(char *s)
{
	size_t	i;

	i = 0;
	while (s != NULL && s[i] != '\0')
	{
		if (s[i] == '\n' && s[i + 1] == '\0')
			s[i] = '\0';
		i++;
	}
	return (s);
}

char	*ms_repl_readline(ms_repl_prompt_get prompt_getter)
{
	char	*line;

	if (!isatty(STDIN_FILENO))
		return (ms_cut_nl(ft_gnl(STDIN_FILENO)));
	line = ms_repl_rl_wrapper(prompt_getter());
	if (line == NULL)
		return (NULL);
	if (!ft_m3_add(line))
	{
		free(line);
		ms_error_out(EXIT_FAILURE, NULL, errno);
	}
	return (line);
}

// maybe only clear the cache of the used fd one day
// for now just remeber to ft_gnl(-1) before exiting
// this is good enough for now
t_byte	ms_repl(void)
{
	char			*line;
	t_ms_parse_res	*parsing_result;

	while (true)
	{
		line = ms_repl_readline(ms_repl_prompt_shell);
		if (line == NULL)
			break ;
		ms_repl_history_add(line);
		parsing_result = ms_parse(line);
		if (!parsing_result->success)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s\n",
				parsing_result->source.error_msg);
			if (!isatty(STDIN_FILENO))
				ms_exit(2);
			else
				ms_env_set_status(2);
		}
		else
			ms_exec(parsing_result->source.cmds);
		ft_free(line);
		ms_free_parser_result(parsing_result);
	}
	return (ms_env_get_status());
}
