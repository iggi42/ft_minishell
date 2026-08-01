/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_set_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 23:52:32 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_iol.h"
#include "libft_toa.h"
#include "libft_fmt_ops.h"
#include "libft_locale.h"

void	ft_fmt_set_hex(t_iol_el *el, unsigned int x)
{
	char		*s;
	const char	*alphabet;

	if (*(el->buffer + 1) == 'x')
		alphabet = FT_ALPHABET_HEX_LOW;
	else
		alphabet = FT_ALPHABET_HEX;
	s = ft_ultoa_b(x, alphabet);
	el->free = ft_iol_free_always;
	ft_fmt_set_str(el, s);
}
