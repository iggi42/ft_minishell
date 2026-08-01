/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_kv_fold.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:36:05 by fkruger           #+#    #+#             */
/*   Updated: 2026/07/26 17:36:09 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_kv.h"

static void	folding(t_list *kv_ll, void (*fold)(t_kv_pair *pair, void *acc),
		void *acc)
{
	if (!kv_ll)
		return ;
	fold(kv_ll->content, acc);
	folding(kv_ll->next, fold, acc);
}

void	ft_kv_fold(t_kv *store, void (*fold)(t_kv_pair *pair, void *acc),
		void *acc)
{
	if (!store || !(store->_store))
		return ;
	folding(store->_store, fold, acc);
}
