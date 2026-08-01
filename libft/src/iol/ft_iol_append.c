/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iol_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:35:38 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_iol.h"
#include "libft_mem.h"

void	ft_iol_append(t_list **io_l, char *start, size_t size)
{
	t_iol_el	*new_seg;
	t_list		*ll_node;

	new_seg = (t_iol_el *) ft_malloc(sizeof(t_iol_el));
	if (new_seg == NULL)
		return ;
	new_seg->buffer = start;
	new_seg->size = size;
	new_seg->free = NULL;
	ll_node = ft_lstnew(new_seg);
	if (ll_node)
		ft_lstadd_back(io_l, ll_node);
	else
		ft_free(new_seg);
}
