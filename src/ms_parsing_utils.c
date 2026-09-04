#include "../inc/ms_parsing.h"
#include <cstddef>
#include <cstdlib>
#include <stdlib.h>

int	count_cmds(t_token *tokens)
{
	int		counter;
	t_token	*current;

	if (!tokens)
		return (0);
	counter = 1;
	current = tokens;
	while (current)
	{
		if (current->kind == PIPE)
			counter++;
		current = current->next;
	}
	return (counter);
}

void	count_cmd_elements(t_token *tokens, int *args, int *reds)
{
	t_token	*current;

	*args = 0;
	*reds = 0;
	current = tokens;
	while (current && current->kind != PIPE)
	{
		if (is_redirect(current->kind))
		{
			(*reds)++;
			current = current->next;
		}
		else
			(*args)++;
		current = current->next;
	}
}

int	alloc_cmd_array(t_ms_cmd *cmds, t_token *tokens)
{
	int	args_count;
	int	reds_count;

	count_cmd_elements(tokens, &args_count, &reds_count);
	cmds->argv = malloc(sizeof(char *) * (args_count + 1));
	if (!cmds->argv)
		return (0);
	cmds->reds = malloc(sizeof(t_ms_redi) * (reds_count + 1));
	if (!cmds->reds)
		return (free(cmds->argv), 0);
	cmds->argv[args_count] = NULL;
	cmds->reds[reds_count] = NULL;
	return (1);
}

t_ms_redi	*redi_builder(char *redi_path, int kind)
{
	t_ms_redi	*redi;

	redi = malloc(sizeof(t_ms_redi));
	if (!redi)
		return (NULL);
	redi->kind = kind;
	redi->source_kind = PATH;
	redi->source.path = redi_path;
	return (redi);
}

void	fill_cmd(t_token **current, t_ms_cmd *cmds)
{
	//populate cmds
}
