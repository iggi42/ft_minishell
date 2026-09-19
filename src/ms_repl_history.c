/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_repl_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:11:43 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 12:11:50 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

void	ms_repl_history_add(char *line)
{
	if (line == NULL)
		return ;
	if (isatty(STDIN_FILENO) == 0)
		return ;
	if (*line != '\0')
		add_history(line);
}

void	ms_repl_history_clear(void)
{
	rl_clear_history();
}
