/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:49:49 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:49:50 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec_utils.h"
#include "ms_exit.h"
#include "ms_heredoc.h"
#include "ms_redi.h"
#include "ms_safe.h"
#include "ms_signal.h"
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_mem.h>

static void	reduce_heredocs_to_inputs(t_ms_redi **rest_redis,
		t_ms_heredoc *doc_info)
{
	if (*rest_redis == NULL)
		return ;
	if ((*rest_redis)->kind == REDI_HERE_DOC
		&& (*rest_redis)->source_kind == REDI_SOURCE_PATH)
	{
		ms_redi_turnoff(doc_info->source_redi);
		ms_heredoc_cleanup_ready(doc_info);
		if (doc_info->state == HEREDOC_READY)
		{
			ft_arr_each((t_arr)doc_info->value.lines, ft_free);
			ft_free(doc_info->value.lines);
			doc_info->value.lines = NULL;
		}
		doc_info->value.lines = ms_heredoc_readin((*rest_redis)->source.path);
		doc_info->state = HEREDOC_READY;
		doc_info->source_redi = *rest_redis;
	}
	reduce_heredocs_to_inputs(rest_redis + 1, doc_info);
}

static void	ms_be_hdoc_writer(int *pipe, char **write_me)
{
	ms_close(pipe[R]);
	while (write_me != NULL && *write_me != NULL)
	{
		ft_putendl_fd(*write_me, pipe[W]);
		write_me++;
		ms_signal_consume();
	}
	ms_close(pipe[W]);
	ms_exit(EXIT_SUCCESS);
}

static void	bootup_heredoc_writer(t_ms_heredoc *active_heredoc)
{
	pid_t	writer;
	int		hdoc_pipe[2];

	if (active_heredoc == NULL || active_heredoc->state != HEREDOC_READY)
		return ;
	ms_pipe((int *)&hdoc_pipe);
	writer = ms_fork();
	if (writer == 0)
		ms_be_hdoc_writer(hdoc_pipe, active_heredoc->value.lines);
	ms_close(hdoc_pipe[W]);
	ms_heredoc_cleanup_ready(active_heredoc);
	ms_redi_set_fd(active_heredoc->source_redi, hdoc_pipe[R]);
	active_heredoc->source_redi->kind = REDI_IN;
	active_heredoc->state = HEREDOC_RUNNING;
	active_heredoc->value.writer = writer;
}

void	ms_heredocs_prepare(t_ms_cmd *cmd)
{
	reduce_heredocs_to_inputs(cmd->reds, &cmd->active_heredoc);
	bootup_heredoc_writer(&cmd->active_heredoc);
}

// this does not free!
// it just reset the heredoc and cleans up associated resources of the struct
// depending on the indicated state of it
void	ms_heredoc_cleanup(t_ms_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	ms_redi_turnoff(cmd->active_heredoc.source_redi);
	ms_heredoc_cleanup_ready(&cmd->active_heredoc);
	ms_heredoc_cleanup_running(&cmd->active_heredoc);
}
