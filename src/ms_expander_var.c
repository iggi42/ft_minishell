/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:44:39 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:44:42 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_iol.h"
#include "ms_env.h"
#include "ms_exit.h"
#include "ms_parsing_getlen.h"
#include "ms_safe.h"
#include "ms_token.h"
#include <libft_mem.h>
#include <libft_str.h>

static size_t	ms_expander_next_el(char *str, bool care_about_quotes)
{
	size_t	i;
	bool	single_q;
	bool	double_q;

	i = 0;
	single_q = false;
	double_q = false;
	while (str[i])
	{
		if (care_about_quotes && str[i] == '\'' && double_q == false)
			single_q = !single_q;
		else if (care_about_quotes && str[i] == '\"' && single_q == false)
			double_q = !double_q;
		else if (str[i] == '$' && (!care_about_quotes || single_q == false))
			return (i);
		i++;
	}
	return (i);
}

static t_iol_el	*ms_exp_var_sect(char *s_dollar, size_t *consumed, bool quotes)
{
	char		*var_name;
	t_iol_el	*result;

	*consumed = ms_parsing_varname(s_dollar + 1);
	result = ms_protect(ft_calloc(sizeof(t_iol_el), 1));
	if (*consumed == 0)
	{
		result->buffer = (char *)&"$";
		result->size = 1;
	}
	else
	{
		var_name = ms_substr(s_dollar, 1, *consumed);
		result->buffer = ms_env_get(var_name, "");
		if (quotes)
		{
			result->buffer = ms_quote_hide(result->buffer);
			result->free = ft_iol_free_always;
		}
		result->size = ft_strlen(result->buffer);
		ft_free(var_name);
	}
	(*consumed)++;
	return (result);
}

static t_iol_el	*ms_exp_nxt_sect(char *s, size_t *consumed, bool quotes)
{
	t_iol_el	*result;

	result = NULL;
	if (*s == '\0')
		return (NULL);
	if (*s == '$')
		result = ms_exp_var_sect(s, consumed, quotes);
	if (result)
		return (result);
	*consumed = ms_expander_next_el(s, quotes);
	result = ms_protect(ft_calloc(sizeof(t_iol_el), 1));
	result->buffer = s;
	result->size = *consumed;
	return (result);
}

void	ms_expand_str(char **s, bool quotes)
{
	t_iol		expanded;
	size_t		consumed;
	char		*runner;
	t_iol_el	*nxt_el;

	runner = *s;
	expanded = NULL;
	nxt_el = ms_exp_nxt_sect(runner, &consumed, quotes);
	while (nxt_el)
	{
		ft_lstadd_back(&expanded, ms_protect(ft_lstnew(nxt_el)));
		runner += consumed;
		nxt_el = ms_exp_nxt_sect(runner, &consumed, quotes);
	}
	runner = ms_protect(ft_iol_str(expanded));
	ft_iol_del(&expanded);
	ft_free(*s);
	*s = runner;
}

/*
void	ms_expand(t_token **list)
{
	t_token	*current;
	t_token	*prev_token;

	current = *list;
	prev_token = NULL;
	while (current)
	{
		if (current->kind == T_WORD && (prev_token == NULL
				|| prev_token->kind != T_HERE_DOC))
			ms_expand_str(&current->value, true);
		prev_token = current;
		current = current->next;
	}
	del_empty_token(list);
	current = *list;
	prev_token = NULL;
	while (current)
	{
		if (current->kind == T_WORD && (prev_token == NULL
				|| prev_token->kind != T_HERE_DOC))
			current->value = ms_quote_show(remove_quote(current->value));
		prev_token = current;
		current = current->next;
	}
}
	*/
