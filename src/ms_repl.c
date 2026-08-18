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

#include "ms_exec.h"
#include "ms_parsing.h"
#include "ms_utils.h"
#include "ms_env.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <libft_char.h>

char *ms_readline(void)
{
	char *line = readline("minishell> ");
	ms_exit_if(line, "exit");
	if(line[0] != '\0' && line[0] != ' ')
		add_history(line);
	return line;
}


void ms_repl(void)
{
	char *line;
	t_ms_parse_res *parsing_result;

	while(true)
	{
		line = ms_readline();
		parsing_result = ms_parse(line);
		if(!parsing_result->success)
		{}
	}
}
