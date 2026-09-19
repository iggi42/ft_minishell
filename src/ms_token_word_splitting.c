/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_word_splitting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:23:28 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/19 15:23:29 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_safe.h"
#include "ms_token.h"
#include <libft_str.h>

// returns the pointer of start where the word ends
static char	*ms_word_size(char *start, size_t *word_size)
{
	char	active_quotes;

	active_quotes = -1;
	*word_size = 0;
	while (start[*word_size] != '\0')
	{
		if (active_quotes == -1 && ms_ws_is_quote(start[*word_size]))
			active_quotes = start[*word_size];
		else if (active_quotes != -1 && start[*word_size] == active_quotes)
			active_quotes = -1;
		else if (active_quotes == -1 && ms_ws_is_in_ifs(start[*word_size]))
			break ;
		(*word_size)++;
	}
	return (start + *word_size);
}

// returns the point of the string where the split word ends
static char	*ms_word_axe(char *start, bool *is_word_start, size_t *word_size)
{
	if (*start == '\0' || ms_ws_is_in_ifs(*start))
	{
		*is_word_start = false;
		return (start);
	}
	*is_word_start = true;
	return (ms_word_size(start, word_size));
}

t_token	*ms_word_spaltwerk(char *input_str)
{
	bool	is_word_start;
	size_t	word_size;
	t_token	*fresh_tokens;
	char	*cont;
	char	*fresh_word;

	fresh_tokens = NULL;
	while (input_str)
	{
		cont = ms_word_axe(input_str, &is_word_start, &word_size);
		if (is_word_start)
		{
			fresh_word = ms_substr(input_str, 0, word_size);
			append_token(&fresh_tokens, fresh_word, T_WORD);
		}
		if (*cont == '\0')
			break ;
		input_str = cont + 1;
	}
	return (fresh_tokens);
}

t_token	*ms_token_lst(t_token *start)
{
	t_token	*lst_tkn;

	if (start == NULL)
		return (NULL);
	lst_tkn = start;
	while (start)
	{
		lst_tkn = start;
		start = start->next;
	}
	return (lst_tkn);
}

t_token	*ms_word_split(t_token **wrd)
{
	t_token	*insert_me;
	t_token	*cont;

	if (wrd == NULL || *wrd == NULL)
		return (NULL);
	insert_me = ms_word_spaltwerk((*wrd)->value);
	if (insert_me == NULL)
		return ((*wrd)->next);
	cont = ms_token_lst(insert_me);
	cont->next = (*wrd)->next;
	free_token(*wrd);
	*wrd = insert_me;
	return (cont);
}
