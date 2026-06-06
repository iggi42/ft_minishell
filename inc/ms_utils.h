/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:04:10 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 19:04:12 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H
# include <stddef.h>

// ms_exit_if(ft_malloc(size), "malloc failed");
void					*ms_exit_if(void *cond, const char *error_msg);

enum					e_iter_res
{
	YES,
	NO,
	NXT
};

typedef struct s_stm_change
{
	enum e_iter_res		res;
	struct s_stm_change	(*next_decision)(int c);
}						t_stm_change;

typedef t_stm_change	(*t_stm_dec)(int c);

// eine funktion entscheided ob der das aktuell teil des sets ist
// oder was die nächste aktion ist um es raus zu finden.
// return types: yes, no, {:more_work, next_fn}
// ms_stm returns a positive number if statemachines finds a match,
// otherwise returns 0
size_t					ms_stm(char *data, t_stm_change *entry);

#endif
