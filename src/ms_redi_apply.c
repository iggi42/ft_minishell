#include "ms_exit.h"
#include "ms_redi.h"
#include "ms_safe.h"
#include "ms_exec_utils.h"
#include <errno.h>

static int	(*get_opn(enum e_ms_redi_kind k))(char *target)
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

void	ms_redi_apply(t_ms_redi *apply_me)
{
	int	fd;
	int	target;

	if (apply_me == NULL || apply_me->kind == REDI_INVALID)
		return ;
	errno = 0;
	if (apply_me->source_kind == REDI_SOURCE_FD)
		fd = apply_me->source.fd;
	else if (apply_me->source_kind == REDI_SOURCE_PATH)
		fd = get_opn(apply_me->kind)(apply_me->source.path);
	else
	{
		// TODO maybe we need to be less aggressiev 
		fd = (ms_error_out(EXIT_FAILURE, ERR_MSG_REDI_SRC, 0), -1);
	}
	if (apply_me->kind == REDI_OUT || apply_me->kind == REDI_OUT_APPEND)
		target = STDOUT_FILENO;
	else
		target = STDIN_FILENO;
	ms_dup2(fd, target);
}
