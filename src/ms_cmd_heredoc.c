#include "libft_arr_t.h"
#include "libft_str.h"
#include "ms_cmd_t.h"
#include "ms_exec_utils.h"
#include "ms_exit.h"
#include "ms_redi.h"
#include "ms_redi_t.h"
#include "ms_repl.h"
#include "ms_safe.h"
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_ll.h>
#include <libft_mem.h>
#include <stdlib.h>
#include <unistd.h>

typedef t_arr_el	(*ft_iter)(void *);

t_arr	*build_arr_from_iter(ft_iter itr, void *iter_arg)
{
	t_arr		*result;
	t_list		*cache;
	t_arr_el	new;

	cache = NULL;
	while (42)
	{
		new = itr(iter_arg);
		if (new == NULL)
			break ;
		ft_lst_push(&cache, new);
	}
	result = ft_lst2arr(cache);
	ft_lstclear(&cache, ft_void);
	ft_arr_rev((t_arr)result);
	return (result);
}

char	*ms_gnl_heredoc(char *delimiter)
{
	char	*line;

	line = ms_gnl(ms_repl_prompt_heredoc);
	if (ft_str_eq(line, delimiter))
		return (ft_free(line), NULL);
	// TODO replace env vars in line if delimiter is not quoted
	// ft_printf_fd(STDERR_FILENO, " heredoc line: [%s]\n", line);
	return (line);
}

char	**ms_heredoc_readin(char *delimiter)
{
	return (char **)build_arr_from_iter((ft_iter)ms_gnl_heredoc, delimiter);
}

static void	reduce_heredocs_to_inputs(t_ms_redi **rest_redis,
		t_ms_heredoc *doc_info)
{
	if (*rest_redis == NULL)
		return ;
	if ((*rest_redis)->kind == REDI_HERE_DOC)
	{
		// TODO remove this "if" sanity check after development,
		// should always be true
		if ((*rest_redis)->source_kind == REDI_SOURCE_PATH)
		{
			ms_redi_turnoff(doc_info->source_redi);
			if (doc_info->state == HEREDOC_READY)
			{
				ft_arr_each((t_arr)doc_info->value.lines, ft_free);
				ft_free(doc_info->value.lines);
			}
			doc_info->value.lines = ms_heredoc_readin((*rest_redis)->source.path);
			doc_info->state = HEREDOC_READY;
			doc_info->source_redi = *rest_redis;
		}
		else
			(void)write(2, "WTF!\n", 5);
	}
	reduce_heredocs_to_inputs(rest_redis + 1, doc_info);
}

static void	be_hdoc_writer(int *pipe, char **write_me)
{
	ms_close(pipe[R]);
	while (write_me != NULL)
	{
		// TODO clean write useage (in chunks smaller than pipe buffer please,
		//	and ms_exit on error)
		ft_putendl_fd(*write_me, pipe[W]);
		write_me++;
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
		be_hdoc_writer(hdoc_pipe, active_heredoc->value.lines);
	ms_close(hdoc_pipe[W]);
	ms_redi_set_fd(active_heredoc->source_redi, hdoc_pipe[R]);
	active_heredoc->source_redi->kind = REDI_IN;
	active_heredoc->state = HEREDOC_RUNNING;
}

void	ms_heredocs_prepare(t_ms_cmd *cmd)
{
	reduce_heredocs_to_inputs(cmd->reds, &cmd->active_heredoc);
	bootup_heredoc_writer(&cmd->active_heredoc);
}

static void	ms_heredoc_cleanup_running(t_ms_heredoc *chd)
{
	if (chd->state != HEREDOC_RUNNING)
		return ;
	if (chd->value.writer > 0)
		ms_wait(chd->value.writer);
	chd->value.writer = 0;
	chd->state = HEREDOC_NO;
}

static void	ms_heredoc_cleanup_ready(t_ms_heredoc *chd)
{
	if (chd->state != HEREDOC_READY)
		return ;
	ft_arr_each((t_arr)chd->value.lines, ft_free);
	ft_free(chd->value.lines);
	chd->state = HEREDOC_NO;
}

// this does not free!
// it just reset the heredoc and cleans up associated resources of the struct
// depending on the indicated state of it
void	ms_heredoc_cleanup(t_ms_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	ms_heredoc_cleanup_ready(&cmd->active_heredoc);
	ms_heredoc_cleanup_running(&cmd->active_heredoc);
}
