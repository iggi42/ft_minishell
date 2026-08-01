/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_lst_kv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LST_KV_H
# define LIBFT_LST_KV_H

# include "libft_ll.h"

typedef t_list	*t_kv_store;
typedef void	*t_kv_value;
typedef void	*t_kv_key;

typedef struct s_kv_pair
{
	t_kv_key	key;
	t_kv_value	val;
}				t_kv_pair;

#endif
