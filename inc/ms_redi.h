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

void	redi_set_path(t_ms_redi *r, char *path);
void	redi_set_fd(t_ms_redi *r, int fd);

void	apply_redi(t_ms_redi *apply_me);
#endif
