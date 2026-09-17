#include "libft_arr_t.h"
#include "libft_str.h"
#include "ms_rl_hooks.h"
#include "ms_cmd_t.h"
#include "ms_exec_utils.h"
#include "ms_exit.h"
#include "ms_signal.h"
#include "ms_parsing.h"
#include "ms_redi.h"
#include "ms_env.h"
#include "ms_redi_t.h"
#include "ms_repl.h"
#include "ms_safe.h"
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_ll.h>
#include <libft_mem.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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
	chd->value.lines = NULL;
	chd->state = HEREDOC_NO;
}

static bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

// returns NULL if the input delimter was not quoted
static char	*unquoted_delimiter(char *delimiter)
{
	size_t input_len;

	if (delimiter == NULL)
		return (NULL);
	input_len = ft_strlen(delimiter);
	if (input_len > 2 && is_quote(delimiter[0]) && delimiter[0] == delimiter[input_len - 1])
		return ms_substr(delimiter, 1, input_len - 2);
	return (NULL);
}

char	*ms_gnl_heredoc(char *delimiter)
{
	char	*line;
	char	*expanded;
	char	*unq_deli;
	char *expander_cache;

	if(ms_signal_last() == SIGINT)
		return (NULL);
	line = ms_repl_readline(ms_repl_prompt_heredoc, ms_rl_heredoc_event_hook);
	if(ms_env_get_status() != 0)
		return (NULL);
	if(line == NULL || ms_signal_last() == SIGINT)
		return (NULL);

	unq_deli = unquoted_delimiter(delimiter);
	// abort if input deli unquoted and line == delimiter
	if (unq_deli == NULL && ft_str_eq(line, delimiter))
		return (ft_free(line), ft_free(unq_deli), NULL);

	// abort if input deli was quoted and the unquoted version == line
	if (unq_deli != NULL && ft_str_eq(line, unq_deli))
		return (ft_free(line), ft_free(unq_deli), NULL);
	// if delimiter is not in quotes
	if(unq_deli == NULL)
	{
		expander_cache = ms_expand_var(line, false);
		expanded = ms_strdup(expander_cache);
		ft_free(line);
		ft_free(expander_cache);
		return expanded;
	}
	// else if delimer is in quotes
	ft_free(unq_deli);
	return (line);
}

char	**ms_heredoc_readin(char *delimiter)
{
	return (char **)ft_arr_from_iter((ft_iter)ms_gnl_heredoc, delimiter);
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
	}
	reduce_heredocs_to_inputs(rest_redis + 1, doc_info);
}

static void	be_hdoc_writer(int *pipe, char **write_me)
{
	ms_close(pipe[R]);
	while (write_me != NULL && *write_me != NULL)
	{
		// TODO clean write useage (in chunks smaller than pipe buffer please)
		ft_putendl_fd(*write_me, pipe[W]);
		write_me++;
		ms_signal_consume();
	}
	ms_close(pipe[W]);
	ms_exit(42);
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
	ms_heredoc_cleanup_ready(&cmd->active_heredoc);
	ms_heredoc_cleanup_running(&cmd->active_heredoc);
}
