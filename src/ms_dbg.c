

#include "libft_arr.h"
#include "libft_arr_t.h"
#include "ms_cmd_t.h"
#include "ms_redi_t.h"
#include "ms_token.h"
#include <libft_io.h>

void	print_arg(char *s)
{
	ft_printf("argument: [%s]\n", s);
}

void	print_redi(t_ms_redi *redi)
{
	if (redi == NULL)
	{
		ft_printf("NULL redi\n");
		return ;
	}
	ft_printf("redi: %d with path: %s\n", redi->kind, redi->source.path);
}

void	ms_print_cmd(char *prefix, t_ms_cmd *cmd)
{
	if (cmd == NULL)
	{
		ft_printf("%s: NULL\n", prefix);
		return ;
	}
	ft_printf("%s:\n", prefix);
	ft_arr_each((t_arr)(cmd->argv), (void (*)(t_arr_el))print_arg);
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))print_redi);
}

void	ms_print_tokens(t_token *tkns)
{
	t_token	*start;

	start = tkns;
	while (tkns)
	{
		if (0 >= ft_printf("token(%d): [%s]\n", tkns->kind, tkns->value))
			break ;
		tkns = tkns->next;
	}
}
