/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_set_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 23:53:20 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_locale.h"
#include "libft_iol.h"
#include "libft_toa.h"
#include "libft_fmt_ops.h"

void	ft_fmt_set_ptr(t_iol_el *el, void *ptr)
{
	char	*s;

	if (ptr == NULL)
		s = "(nil)";
	else
	{
		s = ft_ptoa_b(ptr, FT_ALPHABET_HEX_LOW);
		el->free = ft_iol_free_always;
	}
	ft_fmt_set_str(el, s);
}
