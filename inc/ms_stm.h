/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_stm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:04:10 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 19:04:12 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STM_H
# define MS_STM_H
# include <stddef.h>

typedef struct s_ms_stm_pnt
{
	size_t					size;
	struct s_ms_stm_pnt (*nxt)(char *);
}							t_ms_stm_pnt;

typedef t_ms_stm_pnt (*t_ms_stm_entry)(char *);


size_t ms_stm_match(char *input, t_ms_stm_entry start);


// typedef size_t (*joa)(t_kv_key, t_kv_key);

#endif
