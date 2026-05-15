/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iol_el_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/07 04:02:49 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_iol.h"
#include "libft_mem.h"

t_iol_el	*ft_iol_el_alloc(size_t size)
{
	t_iol_el	*seg;
	char		*start;

	seg = (t_iol_el *) ft_malloc(sizeof(t_iol_el));
	start = (char *)ft_malloc(size);
	if (seg == NULL || start == NULL)
		return (ft_free(seg), ft_free(start), NULL);
	seg->buffer = start;
	seg->size = size;
	seg->free = ft_iol_free_always;
	return (seg);
}
