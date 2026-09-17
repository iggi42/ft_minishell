/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:52:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 18:52:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_cmd_t.h"
#include "ms_exit.h"
#include "ms_parsing.h"
#include "ms_parsing_utils.h"
#include "ms_redi_t.h"
#include "ms_safe.h"
#include "ms_token.h"
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_ll.h>
#include <libft_mem.h>
#include <libft_str.h>

// this returns the next element from inputs
static t_nxt_el	get_next_elemnt(t_token **tkn_start, bool *is_redi)
{
	t_nxt_el	nxt_el;

	ft_bzero(&nxt_el, sizeof(nxt_el));
	*is_redi = (*tkn_start)->kind != T_WORD;
	if (!*is_redi)
	{
		nxt_el.arg = ms_strdup((*tkn_start)->value);
		*tkn_start = (*tkn_start)->next;
	}
	else if ((*tkn_start)->next != NULL && ((*tkn_start)->kind == T_IN
			|| (*tkn_start)->kind == T_OUT || (*tkn_start)->kind == T_HERE_DOC
			|| (*tkn_start)->kind == T_OUT_APPEND))
	{
		nxt_el.redi = redi_builder(ms_strdup((*tkn_start)->next->value),
				(*tkn_start)->kind);
		*tkn_start = (*tkn_start)->next->next;
	}
	return (nxt_el);
}

void	ft_lstclear_all(t_list **arg_stck, t_list **redi_stck)
{
	ft_lstclear(arg_stck, ft_void);
	ft_lstclear(redi_stck, ft_void);
}

static bool	build_cmd_struct(t_ms_cmd **new_cmd, t_token **inputs)
{
	bool		is_redi;
	t_nxt_el	nxt_el;
	t_list		*redi_stck;
	t_list		*arg_stck;

	redi_stck = NULL;
	arg_stck = NULL;
	while (*inputs != NULL && (*inputs)->kind != T_PIPE)
	{
		nxt_el = get_next_elemnt(inputs, &is_redi);
		if (nxt_el.arg == NULL)
		{
			if (*inputs == NULL)
				break ;
			else
				return (false);
		}
		if (is_redi)
			ft_lst_push(&redi_stck, nxt_el.redi);
		else
			ft_lst_push(&arg_stck, nxt_el.arg);
	}
	*new_cmd = ms_cmd_new(redi_stck, arg_stck);
	ft_lstclear_all(&arg_stck, &redi_stck);
	return (true);
}

static t_ms_cmd	**build_cmd_arr(t_token *tkn)
{
	t_ms_cmd	**result;
	size_t		amount;
	size_t		i;

	amount = ms_parsing_count_cmds(tkn);
	i = 0;
	result = (t_ms_cmd **)ms_protect(ft_arr_new(amount));
	while (i < amount && tkn != NULL)
	{
		if (!build_cmd_struct(&result[i++], &tkn))
		{
			ft_arr_each((t_arr)result, (void (*)(t_arr_el))ms_cmd_free);
			ft_free(result);
			return (NULL);
		}
		if (tkn == NULL)
			break ;
		tkn = tkn->next;
	}
	return (result);
}

t_ms_parse_res	*ms_parse(char *input)
{
	t_ms_parse_res	*result;
	t_token			*tkns;

	tkns = ms_tokenize(input);
	result = ms_malloc(sizeof(t_ms_parse_res));
	result->source.error_msg = ms_syntax_check(tkns);
	result->success = (result->source.error_msg == NULL);
	if (result->success)
	{
		ms_expand(&tkns);
		result->source.cmds = build_cmd_arr(tkns);
		if (result->source.cmds == NULL)
		{
			result->success = false;
			result->source.error_msg = ms_strdup("syntax error");
		}
	}
	free_token_list(tkns);
	return (result);
}
