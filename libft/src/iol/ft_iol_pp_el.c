/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iol_pp_el.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_io.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_iol.h"

void	ft_iol_pp_el(t_iol_el *el)
{
	char	*s;

	if (el == NULL)
	{
		ft_printf("[NULL] io element\n");
		return ;
	}
	s = ft_substr(el->buffer, 0, el->size);
	ft_printf("%d : [%s]\n", el->size, s);
	ft_free(s);
}
