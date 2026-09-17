/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:44:26 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/19 17:44:27 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bw.h"
#include "ms_exec_utils.h"
#include "ms_exit.h"
#include "ms_redi.h"
#include "ms_redi_t.h"
#include "ms_safe.h"
#include <errno.h>
#include <libft_io.h>
#include <libft_mem.h>
#include <libft_str.h>

void	ms_redi_turnoff(t_ms_redi *redi)
{
	if (redi == NULL || redi->kind == REDI_INVALID)
		return ;
	if (redi->source_kind == REDI_SOURCE_PATH)
		redi->source.path = (ft_free(redi->source.path), NULL);
	if (redi->source_kind == REDI_SOURCE_FD && redi->source.fd >= 0)
		redi->source.fd = (ms_close(redi->source.fd), -1);
	redi->kind = REDI_INVALID;
}

// do we also want to close the fds with that? probably, right?
void	ms_redi_free(t_ms_redi *redi)
{
	if (redi == NULL)
		return ;
	ms_redi_turnoff(redi);
	ft_free(redi);
}

void	ms_redi_set_path(t_ms_redi *r, char *path)
{
	if (r == NULL)
		return ;
	ms_redi_turnoff(r);
	r->source_kind = REDI_SOURCE_PATH;
	r->source.path = path;
}

void	ms_redi_set_fd(t_ms_redi *r, int fd)
{
	if (r == NULL)
		return ;
	ms_redi_turnoff(r);
	r->source_kind = REDI_SOURCE_FD;
	r->source.fd = fd;
}
