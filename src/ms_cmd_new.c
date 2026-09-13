#include "ms_cmd_t.h"
#include "ms_exit.h"
#include "ms_safe.h"
#include <libft_arr.h>

t_ms_cmd	*ms_cmd_new(t_list *redi_stack, t_list *argv_stack)
{
	t_ms_cmd	*new_cmd;

	new_cmd = ms_malloc(sizeof(t_ms_cmd));
	new_cmd->active_heredoc.source_redi = NULL;
	new_cmd->active_heredoc.state = HEREDOC_NO;
	new_cmd->active_heredoc.value.lines = NULL;
	new_cmd->argv = (char **)ms_protect(ft_lst2arr(argv_stack));
	new_cmd->reds = (t_ms_redi **)ms_protect(ft_lst2arr(redi_stack));
	ft_arr_rev((t_arr)new_cmd->argv);
	ft_arr_rev((t_arr)new_cmd->reds);
	return (new_cmd);
}
