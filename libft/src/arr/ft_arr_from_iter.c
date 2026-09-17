/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_from_iter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:21:09 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 12:21:11 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_arr.h>
#include <libft_ll.h>
#include <libft_mem.h>

t_arr	*ft_arr_from_iter(t_iter itr, void *iter_arg)
{
	t_arr		*result;
	t_list		*cache;
	t_arr_el	new;

	cache = NULL;
	while (42)
	{
		new = itr(iter_arg);
		if (new == NULL)
			break ;
		ft_lst_push(&cache, new);
	}
	result = ft_lst2arr(cache);
	ft_lstclear(&cache, ft_void);
	ft_arr_rev((t_arr)result);
	return (result);
}
