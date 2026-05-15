/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_kv_each.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:57:43 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/23 13:57:44 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_kv.h"
#include "libft_lst_kv.h"

void ft_kv_each(t_kv *store, void (*each)(t_kv_pair *pair))
{
	if(!store)
		return ;
	ft_lstiter(store->_store, (void (*)(void *)) each);
}
