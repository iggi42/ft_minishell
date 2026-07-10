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
#include "ms_parsing.h"
#include <libft_char.h>
#include <libft_ll.h>
#include <stdbool.h>

// demonstrate the syntax statemachine by checking how to find blanks
t_ms_stm_pnt	ms_stm_word(char *input)
{
	t_ms_stm_pnt	result;
	result.size = 0;
	if(ms_is_metachar(*input))
		return result;

	return result;
}
