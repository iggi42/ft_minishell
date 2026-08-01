/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iol_str_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_iol.h"
#include "libft_mem.h"

size_t	ft_iol_str_l(t_list *list, char *target, size_t length)
{
	size_t		len;
	size_t		target_i;
	t_iol_el	*el;

	len = ft_iol_size(list);
	target_i = 0;
	if (len > length)
		return (len);
	while (list != NULL && target != NULL)
	{
		el = (t_iol_el *)list->content;
		ft_memcpy(target + target_i, el->buffer, el->size);
		target_i += el->size;
		list = list->next;
	}
	return (target_i);
}
