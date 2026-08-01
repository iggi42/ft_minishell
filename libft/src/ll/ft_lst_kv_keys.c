/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_kv_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:10:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_arr.h"
#include "libft_kv.h"
#include "libft_ll.h"
#include "libft_lst_kv.h"

//! get all keys in a freeable, NULL terminated array
t_kv_key	*ft_kv_keys(t_kv *store)
{
	size_t	s;
	size_t	i;
	t_arr	*result;
	t_list	*head;

	i = 0;
	head = store->_store;
	s = ft_lstsize(store->_store);
	result = ft_arr_new(s);
	while (i < s)
	{
		*(result + i++) = ((t_kv_pair *)head->content)->key;
		head = head->next;
	}
	return ((t_kv_key *)result);
}
