/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_kv.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_KV_H
# define LIBFT_KV_H

// default types for now
# include "libft_lst_kv.h"

typedef int			(*t_kv_key_cmp)(t_kv_key, t_kv_key);

typedef struct s_kv
{
	t_kv_key_cmp	key_cmp;
	t_kv_store		_store;
}					t_kv;

t_kv				*ft_kv_init(const t_kv_key_cmp key_cmp);
void				ft_kv_free(t_kv *store);

/** returns NULL if not found */
t_kv_value			ft_kv_get(t_kv *store, t_kv_key key);

// pop is same as get, but removes a found entry from store
t_kv_pair	*ft_kv_pop(t_kv *root, t_kv_key key);

void				ft_kv_put(t_kv *store, t_kv_key key, t_kv_value v);

/** get all keys in a NULL terminated array */
t_kv_key			*ft_kv_keys(t_kv *store);

/** call each for each key value pair */
void ft_kv_each(t_kv *store, void (*each)(t_kv_pair *pair));

#endif
