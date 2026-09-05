#include "ms_parsing.h"
#include "ms_redi_t.h"
#include "ms_token.h"
#include "ms_utils.h"
#include <stdlib.h>

size_t	ms_parsing_count_cmds(t_token *tokens)
{
	size_t	counter;

	if (!tokens)
		return (0);
	counter = 1;
	while (tokens != NULL)
	{
		if (tokens->kind == T_PIPE)
			counter++;
		tokens = tokens->next;
	}
	return (counter);
}

void	count_cmd_elements(t_token *tokens, int *args, int *reds)
{
	t_token	*current;

	*args = 0;
	*reds = 0;
	current = tokens;
	while (current && current->kind != T_PIPE)
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
	cmds->argv = ms_malloc(sizeof(char *) * (args_count + 1));
	if (!cmds->argv)
		return (0);
	cmds->reds = ms_malloc(sizeof(t_ms_redi) * (reds_count + 1));
	if (!cmds->reds)
		return (free(cmds->argv), 0);
	cmds->argv[args_count] = NULL;
	cmds->reds[reds_count] = NULL;
	return (1);
}

static enum e_ms_redi_kind	convert_redi_kind(t_toke_type tkn_type)
{
	if (tkn_type == T_IN)
		return (REDI_IN);
	if (tkn_type == T_OUT)
		return (REDI_OUT);
	if (tkn_type == T_OUT_APPEND)
		return (REDI_OUT_APPEND);
	if (tkn_type == T_HERE_DOC)
		return (REDI_HERE_DOC);
	return (REDI_INVALID);
}

t_ms_redi	*redi_builder(char *redi_path, t_toke_type kind)
{
	t_ms_redi	*redi;

	redi = ms_malloc(sizeof(t_ms_redi));
	redi->kind = convert_redi_kind(kind);
	redi->source_kind = REDI_SOURCE_PATH;
	redi->source.path = redi_path;
	return (redi);
}
