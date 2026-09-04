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
#include "ms_parsing.h"
#include "ms_token.h"
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_mem.h>
#include <libft_str.h>

void	print_tokens(char *input)
{
	t_token	*tkns;
	t_token	*start;

	tkns = ms_tokenize(input);
	start = tkns;
	while (tkns)
	{
		if (0 >= ft_printf("token(%d): [%s]\n", tkns->kind, tkns->value))
			break ;
		tkns = tkns->next;
	}
	free_token_list(start);
}

t_ms_parse_res	*ms_parse(char *input)
{
	t_ms_parse_res	*result;

	print_tokens(input);
	result = ft_malloc(sizeof(t_ms_parse_res));
	result->success = false;
	result->source.error_msg = ft_strdup(input);
	return (result);
}
