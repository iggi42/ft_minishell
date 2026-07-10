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
#include "ms_stm.h"
#include <libft_char.h>
#include <libft_ll.h>
#include <stdbool.h>

static bool	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

// demonstrate the syntax statemachine by checking how to find blanks
t_ms_stm_pnt	ms_stm_blnk(char *input)
{
	t_ms_stm_pnt	result;

	result.nxt = NULL;
	result.size = 0;
	while (is_blank(input[result.size]))
		result.size++;
	return (result);
}
