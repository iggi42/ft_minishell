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
#include "ms_token.h"
#include "ms_parsing.h"
#include "ms_utils.h"
#include <errno.h>
#include <libft_char.h>
#include <libft_mem.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static char	*ms_gnl(void)
{
	char	*line;

	if (!isatty(STDIN_FILENO))
		return (ft_gnl(STDIN_FILENO));
	line = readline(ms_get_env("PS1", "minishell> "));
	if (line == NULL)
		return (NULL);
	if (!ft_m3_add(line))
		return (ms_error_out(EXIT_FAILURE, NULL, errno), NULL);
	if (line[0] != '\0')
		add_history(line);
	return (line);
}

int	ms_repl(void)
{
	char			*line;
	t_ms_parse_res	*parsing_result;
	t_byte exit_code;

	exit_code = 0;
	while (true)
	{
		line = ms_gnl();
		if(line == NULL)
			break;
		parsing_result = ms_parse(line);
		if (!parsing_result->success)
			ft_printf_fd(STDERR_FILENO, "invalid syntax: %s\n",
				parsing_result->source.error_msg);
		else
			exit_code = ms_run_pipe(&parsing_result->source.cmds);
		ft_free(line);
		ms_free_parser_result(parsing_result);
	}
	return exit_code;
}
