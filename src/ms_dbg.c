

#include "libft_arr.h"
#include "libft_arr_t.h"
#include "ms_cmd_t.h"
#include "ms_parsing.h"
#include "ms_redi_t.h"
#include "ms_token.h"
#include <libft_io.h>

void	print_arg(char *s)
{
	ft_printf("argument: [%s]\n", s);
}

char *redi_type(enum e_ms_redi_kind rk)
{
	if(rk == REDI_INVALID)
		return "REDI_INVALID";
	if(rk == REDI_IN)
		return "REDI_IN";
	if(rk == REDI_OUT)
		return "REDI_OUT";
	if(rk == REDI_OUT_APPEND)
		return "REDI_OUT_APPEND";
	if(rk == REDI_HERE_DOC)
		return "REDI_HERE_DOC";
	return "REDI_WHAT_THE_FUCK";
}

void	print_redi(t_ms_redi *redi)
{
	if (redi == NULL)
	{
		ft_printf("redi [NULL]\n");
		return ;
	}
	if(redi->kind == REDI_INVALID)
		ft_printf("redi: invalid (set source: %d)\n", redi->source_kind);
	else if(redi->source_kind == REDI_SOURCE_PATH)
		ft_printf("redi: %s with path: [%s]\n", redi_type(redi->kind), redi->source.path);
	else if(redi->source_kind == REDI_SOURCE_PATH)
		ft_printf("redi: %s with fd: [%d]\n", redi_type(redi->kind), redi->source.path);
}

char *heredoc_state(enum e_ms_heredoc_state st)
{
	if(st == HEREDOC_NO)
		return "HEREDOC_NO";
	if(st == HEREDOC_RUNNING)
		return "HEREDOC_RUNNING";
	if(st == HEREDOC_READY)
		return "HEREDOC_READY";
	return "HEREDOC_WHAT_THE_FUCK_STATE";
}

// int				exit_code;
// union			u_ms_parse_res_body
// {
// 	char		*error_msg;
// 	t_ms_cmd	**cmds;
// } source;

void print_heredoc_line(char *line)
{
	ft_printf("hdoc: [%s]\n", line);
}

void ms_print_heredoc(t_ms_heredoc *hd)
{
	ft_printf("heredoc state: [%s]\n", heredoc_state(hd->state));
	if(hd->state == HEREDOC_READY)
		ft_arr_each((t_arr) hd->value.lines, (void (*)(t_arr_el)) print_heredoc_line);
	if(hd->state == HEREDOC_RUNNING)
		ft_printf("heredoc writer pid: [%d] [%d]\n", hd->value.writer, ((pid_t) -1) /4 );
}

void ms_print_cmd_anon(t_ms_cmd *cmd)
{
	ms_print_heredoc(&cmd->active_heredoc);
	ft_arr_each((t_arr)(cmd->argv), (void (*)(t_arr_el))print_arg);
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))print_redi);
}

void	ms_print_cmd(char *prefix, t_ms_cmd *cmd)
{
	if (cmd == NULL)
	{
		ft_printf("%s: NULL\n", prefix);
		return ;
	}
	ft_printf("%s:\n", prefix);
	ms_print_cmd_anon(cmd);
}

void	ms_print_tokens(t_token *tkns)
{
	while (tkns)
	{
		if (0 >= ft_printf("token(%d): [%s]\n", tkns->kind, tkns->value))
			break ;
		tkns = tkns->next;
	}
}

void print_parsing_result(char *desc, t_ms_parse_res *res)
{
	ft_printf("parsing result: %s @ %p\n", desc, res);
	ft_printf("exit_code: %d\n", res->exit_code);
	if(res->exit_code == 0)
		ft_arr_each((t_arr) res->source.cmds, (void (*)(t_arr_el)) ms_print_cmd_anon);
}

