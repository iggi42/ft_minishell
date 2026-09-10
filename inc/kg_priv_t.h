/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m3_priv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 05:29:32 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/07 05:29:35 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BW_PRIV_T_H
# define BW_PRIV_T_H
# include <unistd.h>

typedef struct s_kg_el
{
	struct s_kg_el	*next;
	pid_t			pid;
}					t_kg_el;

#endif
