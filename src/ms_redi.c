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
#include "ms_utils.h"
#include "ms_exec_utils.h"
#include "ms_redi.h"
#include <errno.h>
#include <libft_io.h>
#include <libft_str.h>
#include <stdlib.h>
#include <unistd.h>

static int	(*get_opn(enum e_ms_redi_kind k))(char *target)
{
	if (k == IN)
		return (open_infile);
	if (k == OUT)
		return (open_outfile);
	if (k == OUT_APPEND)
		return (open_outappfile);
	ms_error_out(EXIT_FAILURE, "unexpected redirector kind", 0);
	return (NULL);
}

void	redi_set_path(t_ms_redi *r, char *path)
{
	if (r == NULL)
		return ;
	r->source_kind = PATH;
	r->source.path = path;
}

void	redi_set_fd(t_ms_redi *r, int fd)
{
	if (r == NULL)
		return ;
	r->source_kind = FD;
	r->source.fd = fd;
}

void	apply_redi(t_ms_redi *apply_me)
{
	int	fd;
	int	target;

	if (apply_me == NULL)
		return ;
	errno = 0;
	if (apply_me->source_kind == FD)
		fd = apply_me->source.fd;
	else if (apply_me->source_kind == PATH)
		fd = get_opn(apply_me->kind)(apply_me->source.path);
	else
		fd = (ms_error_out(EXIT_FAILURE, ERR_MSG_REDI_SRC, 0), -1);
	ft_bw_add(fd);
	if (apply_me->kind == OUT || apply_me->kind == OUT_APPEND)
		target = STDOUT_FILENO;
	else
		target = STDIN_FILENO;
	ms_dup2(fd, target);
}
