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
#include "ms_repl.h"
#include "ms_token.h"
#include <libft_io.h>
#include <libft_mem.h>
#include <stdlib.h>
#include <unistd.h>

void	print_tokens(size_t id, char *input)
{
	t_token	*tkns;

	tkns = ms_tokenize(input);
	while (tkns)
	{
		if (0 >= ft_printf("(%d)token: [%s]\n", id, tkns->value))
			break ;
		tkns = tkns->next;
	}
}

int	main(int argc, char **argv)
{
	int	exit_code;

	if (argc != 1)
		return ((void)argv, -1);
	ms_load_env(__environ);
	if (isatty(STDIN_FILENO))
		exit_code = ms_repl();
	else
		exit_code = ms_run_from_fd(STDIN_FILENO);
	return (exit_code);
}
