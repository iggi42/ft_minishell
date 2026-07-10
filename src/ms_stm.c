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
#include <libft_ll.h>
#include "ms_stm.h"

size_t ms_stm_match(char *input, t_ms_stm_entry start)
{
	t_ms_stm_pnt nxt;
	if(!start) return 0;

	nxt = start(input);
	if(nxt.size == 0) return 0;
	return (nxt.size + ms_stm_match(input + nxt.size, nxt.nxt));
}

