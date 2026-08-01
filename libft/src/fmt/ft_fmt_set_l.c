/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_set_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 23:53:50 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_iol.h"
#include "libft_toa.h"
#include "libft_fmt_ops.h"

// alphabet padding and leading + options tbd
void	ft_fmt_set_l(t_iol_el *el, long l)
{
	char	*s;

	s = ft_ltoa(l);
	el->free = ft_iol_free_always;
	ft_fmt_set_str(el, s);
}
