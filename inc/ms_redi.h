/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 12:02:46 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 12:02:46 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_REDI_H
# define MS_REDI_H

# include "ms_redi_t.h"

void	ms_redi_set_path(t_ms_redi *r, char *path);
void	ms_redi_set_fd(t_ms_redi *r, int fd);

void	ms_redi_turnoff(t_ms_redi *r);

void	ms_redi_free(t_ms_redi *redi);

// applies a redirector the current process
void	ms_redi_apply(t_ms_redi *apply_me);

// applies them too but is hacky cause it happens without forking
void ms_redi_apply_interactive(t_ms_redi *apply_me);
#endif
