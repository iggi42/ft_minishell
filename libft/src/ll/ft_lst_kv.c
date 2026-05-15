/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_kv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:10:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_kv.h"
#include "libft_ll.h"
#include "libft_lst_kv.h"
#include "libft_mem.h"

void	ft_kv_free(t_kv *kv)
{
	ft_lstclear(&(kv->_store), ft_free);
}

// returns NULL if keys don't match
// else returns the address of value of kv pair
static t_kv_value	*kv_maybe_value(t_kv_pair *pair, t_kv_key key,
		t_kv_key_cmp key_cmp)
{
	if (key == pair->key)
		return (&(pair->val));
	if (key_cmp(key, pair->key) == 0)
		return (&(pair->val));
	return (NULL);
}

//! returns NULL if not found
t_kv_value	ft_kv_get(t_kv *root, t_kv_key key)
{
	t_list		*head;
	t_kv_value	*val;

	if(root == NULL)
		return (NULL);
	head = root->_store;
	while (head != NULL)
	{
		val = kv_maybe_value(head->content, key, root->key_cmp);
		if (val != NULL)
			return (*val);
		head = head->next;
	}
	return (NULL);
}

t_kv_pair	*ft_kv_pop(t_kv *root, t_kv_key key)
{
	t_kv_value	*val;
	t_kv_pair	*result;
	t_list		**head;

	head = &root->_store;
	while (*head != NULL)
	{
		val = kv_maybe_value((*head)->content, key, root->key_cmp);
		if (val != NULL)
		{
			result = (t_kv_pair *) (*head)->content;
			ft_lstdelone(head, ft_free);
			return (result);
		}
		head = &((*head)->next);
	}
	return (NULL);
}

void	ft_kv_put(t_kv *store, t_kv_key key, t_kv_value v)
{
	t_kv_pair	*kv;
	t_kv_value	*val;
	t_list		**head;

	head = &store->_store;
	while (*head != NULL)
	{
		val = kv_maybe_value((*head)->content, key, store->key_cmp);
		if (val != NULL)
		{
			*val = v;
			return ;
		}
		head = &((*head)->next);
	}
	kv = ft_malloc(sizeof(t_kv_pair));
	kv->key = key;
	kv->val = v;
	*head = ft_lstnew(kv);
}
