/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:49:26 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:49:28 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"
#include "libft_str.h"
#include "ms_exit.h"
#include "ms_safe.h"
#include "ms_token.h"
#include <libft_mem.h>

static size_t	unquote_len(char *str)
{
	int		i;
	int		len;
	bool	single_q;
	bool	double_q;

	i = 0;
	len = 0;
	single_q = false;
	double_q = false;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[i] == '\"' && !single_q)
			double_q = !double_q;
		else
			len++;
		i++;
	}
	return (len);
}

static void	unquote_cpy(char *str, char *new_str)
{
	int		i;
	int		j;
	bool	single_q;
	bool	double_q;

	i = 0;
	j = 0;
	single_q = false;
	double_q = false;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[i] == '\"' && !single_q)
			double_q = !double_q;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = 0;
}

char	*remove_quote(char *str)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = ms_malloc(unquote_len(str) + 1);
	unquote_cpy(str, new_str);
	ft_free(str);
	return (new_str);
}

t_token	*remove_token(t_token **list, t_token *previous, t_token *current)
{
	t_token	*next_token;

	next_token = current->next;
	if (previous)
		previous->next = next_token;
	else
		*list = next_token;
	ft_free(current->value);
	ft_free(current);
	return (next_token);
}

int	del_empty_token(t_token **list, char **err_msg)
{
	t_token	*current;
	t_token	*previous;

	current = *list;
	previous = NULL;
	while (current)
	{
		if (current->kind == T_WORD && current->value[0] == 0)
		{
			// TODO check if the prev token is a redirect
			if(previous != NULL && is_redirect(previous->kind))
			{
				*err_msg = ms_strdup("ambiguous redirect\n");
				return (1);
			}
			current = remove_token(list, previous, current);
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
	return (0);
}
