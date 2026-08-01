/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_set_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:52:26 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_iol.h"
#include "libft_str.h"

void	ft_fmt_set_str(t_iol_el *el, char *s)
{
	if (s == NULL)
		return (ft_fmt_set_str(el, "(null)"));
	el->buffer = s;
	el->size = ft_strlen(s);
}
