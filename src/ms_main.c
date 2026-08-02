/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:51:50 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 18:51:53 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_token.h"
#include <libft_io.h>

void print_tokens(size_t id, char *input)
{
	t_token *tkns = ms_tokenize(input);
	while(tkns)
	{
		if(0 >= ft_printf("(%d)token: [%s]\n", id, tkns->value))
			break;
		tkns = tkns->next;
	}
}

int	main(int argc, char **argv)
{
	size_t i = 1;
	while(i < (size_t) argc && argv[i])
		(print_tokens(i, argv[i]), i++);
	return (-1);
}
