/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 16:22:59 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/19 16:23:02 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_heredoc.h"
#include "ms_parsing.h"
#include "ms_repl.h"
#include "ms_rl_hooks.h"
#include "ms_safe.h"
#include "ms_signal.h"
#include "ms_token.h"
#include <libft_arr.h>
#include <libft_mem.h>
#include <libft_str.h>
#include <signal.h>

void	ms_heredoc_cleanup_running(t_ms_heredoc *chd)
{
	if (chd->state != HEREDOC_RUNNING)
		return ;
	if (chd->value.writer > 0)
		ms_wait(chd->value.writer);
	chd->value.writer = 0;
	chd->state = HEREDOC_NO;
}

void	ms_heredoc_cleanup_ready(t_ms_heredoc *chd)
{
	if (chd->state != HEREDOC_READY)
		return ;
	ft_arr_each((t_arr)chd->value.lines, ft_free);
	ft_free(chd->value.lines);
	chd->value.lines = NULL;
	chd->state = HEREDOC_NO;
}

// returns NULL if the input delimiter carried no quotes at all,
// otherwise the delimiter with every quote removed
char	*unquoted_delimiter(char *delimiter)
{
	char	*unquoted;

	if (delimiter == NULL)
		return (NULL);
	unquoted = remove_quote(ms_strdup(delimiter));
	if (ft_strlen(unquoted) != ft_strlen(delimiter))
		return (unquoted);
	return (ft_free(unquoted), NULL);
}

char	*ms_gnl_heredoc(char *delimiter)
{
	char	*line;
	char	*unq_deli;

	if (ms_signal_last() == SIGINT)
		return (NULL);
	line = ms_repl_readline(ms_repl_prompt_heredoc, ms_rl_heredoc_event_hook);
	if (line == NULL)
		return (NULL);
	unq_deli = unquoted_delimiter(delimiter);
	if (unq_deli == NULL && ft_str_eq(line, delimiter))
		return (ft_free(line), ft_free(unq_deli), NULL);
	if (unq_deli != NULL && ft_str_eq(line, unq_deli))
		return (ft_free(line), ft_free(unq_deli), NULL);
	if (unq_deli == NULL)
		ms_expand_str(&line, false);
	ft_free(unq_deli);
	return (line);
}

char	**ms_heredoc_readin(char *delimiter)
{
	return ((char **)ft_arr_from_iter((t_iter)ms_gnl_heredoc, delimiter));
}
