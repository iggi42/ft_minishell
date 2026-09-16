#include "ms_env.h"
#include "ms_exec_utils.h"
#include "ms_exit.h"
#include "ms_redi.h"
#include "ms_redi_t.h"
#include "ms_safe.h"
#include <errno.h>
#include <stdlib.h>

static int (*get_opn(enum e_ms_redi_kind k))(char *target)
{
	if (k == REDI_IN)
		return (ms_open_infile);
	if (k == REDI_OUT)
		return (ms_open_outfile);
	if (k == REDI_OUT_APPEND)
		return (ms_open_outappfile);
	ms_error_out(EXIT_FAILURE, "unexpected redirector kind", 0);
	return (NULL);
}

// TODO set status code according to if the applying worked out
// should only be needed in the parent, in the forked versions we can just exit out directly

void	ms_redi_apply_parent(t_ms_redi *apply_me)
{
	int	fd;
	int	target;

	if (apply_me == NULL || apply_me->kind == REDI_INVALID
		|| ms_env_get_status() != 0)
		return ;
	if (apply_me->source_kind == REDI_SOURCE_FD)
		fd = apply_me->source.fd;
	else if (apply_me->source_kind == REDI_SOURCE_PATH)
	{
		fd = get_opn(apply_me->kind)(apply_me->source.path);
		if (fd < 0)
			return (ms_complain(apply_me->source.path, errno),
				ms_env_set_status(1));
	}
	else
		fd = (ms_env_set_status(EXIT_FAILURE), -1);
	if (apply_me->kind == REDI_OUT || apply_me->kind == REDI_OUT_APPEND)
		target = STDOUT_FILENO;
	else
		target = STDIN_FILENO;
	ms_dup2(fd, target);
}

void	ms_redi_apply(t_ms_redi *apply_me)
{
	int	fd;
	int	target;

	if (apply_me == NULL || apply_me->kind == REDI_INVALID)
		return ;
	if (apply_me->source_kind == REDI_SOURCE_FD)
		fd = apply_me->source.fd;
	else if (apply_me->source_kind == REDI_SOURCE_PATH)
	{
		fd = get_opn(apply_me->kind)(apply_me->source.path);
		if (fd < 0)
			ms_error_out(EXIT_FAILURE, apply_me->source.path, errno);
	}
	else
		fd = (ms_error_out(EXIT_FAILURE, ERR_MSG_REDI_SRC, 0), -1);
	if (apply_me->kind == REDI_OUT || apply_me->kind == REDI_OUT_APPEND)
		target = STDOUT_FILENO;
	else
		target = STDIN_FILENO;
	ms_dup2(fd, target);
}
