/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_repl_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:26:41 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:26:54 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// this logic describes what prompt you see in interactive mode

#include "ms_env.h"
#include <unistd.h>

char	*ms_repl_prompt_shell(void)
{
	if (isatty(STDIN_FILENO) == 0)
		return ("");
	return (ms_env_get("PS1", "minishell %> "));
}

char	*ms_repl_prompt_heredoc(void)
{
	if (isatty(STDIN_FILENO) == 0)
		return ("");
	return (ms_env_get("PS2", "minishell_heredoc %> "));
}
