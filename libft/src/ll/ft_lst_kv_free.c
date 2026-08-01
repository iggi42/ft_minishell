/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_kv_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:35:15 by fkruger           #+#    #+#             */
/*   Updated: 2026/07/26 17:35:19 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_kv.h"
#include "libft_ll.h"
#include "libft_lst_kv.h"
#include "libft_mem.h"

void	ft_kv_free_entry(t_kv_pair *entry)
{
	if (entry == NULL)
		return ;
	ft_free(entry->key);
	ft_free(entry->val);
	ft_free(entry);
}

void	ft_kv_free(t_kv *kv, void (*f)(t_kv_pair *ptr))
{
	if (kv == NULL)
		return ;
	ft_lstclear(&(kv->_store), (void *)f);
	ft_free(kv);
}
