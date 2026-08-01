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

// returns NULL if keys don't match
// else returns the address of value of kv pair
static t_kv_pair	*kv_maybe_value(t_kv_pair *pair, t_kv_key key,
		t_kv_key_cmp key_cmp)
{
	if (key == pair->key)
		return (pair);
	if (key_cmp(key, pair->key) == 0)
		return (pair);
	return (NULL);
}

//! returns NULL if not found
t_kv_value	ft_kv_get(t_kv *root, t_kv_key key)
{
	t_list		*head;
	t_kv_pair	*here;

	if (root == NULL || key == NULL)
		return (NULL);
	head = root->_store;
	while (head != NULL)
	{
		here = kv_maybe_value(head->content, key, root->key_cmp);
		if (here != NULL)
			return (here->val);
		head = head->next;
	}
	return (NULL);
}

t_kv_pair	*ft_kv_pop(t_kv *root, t_kv_key key)
{
	t_kv_pair	*here;
	t_list		**head;

	if (root == NULL || key == NULL)
		return (NULL);
	head = &root->_store;
	while (*head != NULL)
	{
		here = kv_maybe_value((*head)->content, key, root->key_cmp);
		if (here != NULL)
			return (ft_lstdelone(head, ft_void), here);
		head = &((*head)->next);
	}
	return (NULL);
}

static t_kv_pair	*new_kv_pair(t_kv_key key, t_kv_value v)
{
	t_kv_pair	*pair;

	pair = ft_malloc(sizeof(t_kv_pair));
	if (pair == NULL)
		return (NULL);
	pair->key = key;
	pair->val = v;
	return (pair);
}

t_kv_pair	*ft_kv_put(t_kv *root, t_kv_key key, t_kv_value v)
{
	t_kv_pair	*here;
	t_list		**head;

	if (root == NULL || key == NULL)
		return (NULL);
	head = &root->_store;
	while (*head != NULL)
	{
		here = kv_maybe_value((*head)->content, key, root->key_cmp);
		if (here != NULL)
			return ((*head)->content = new_kv_pair(key, v), here);
		head = &((*head)->next);
	}
	*head = ft_lstnew(new_kv_pair(key, v));
	return (NULL);
}
