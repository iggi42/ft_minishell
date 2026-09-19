#include "ms_parsing.h"
#include "ms_token.h"
#include <stdbool.h>
#include <libft_mem.h>

bool	is_ambigous_redi(char *maybe_ambi)
{
	bool	result;
	char	*local_copy;

	local_copy = ms_strdup(maybe_ambi);
	ms_expand_str(&local_copy, true);
	result = ms_line_is_blank(local_copy);
	ft_free(local_copy);
	return (result);
}

// // we know the curent->next is not NULL and a word
// if (is_ambigous_redi(current->next->value))
// 	return (ms_protect(ft_strf(ambi_error_msg, current->next->value)));
// // check if the next word expands to anything here, if it does not
// // it should an ambigious redirect, I think?

static bool ms_expand_var(t_token **current, t_token *prev)
{
	if ((*current)->kind != T_WORD)
		return true;
	if (prev_token != NULL	|| prev_token->kind != T_HERE_DOC))
	
	ms_expand_str(current->value, true);
}

// this function name is a lie, we don't expand the tokens
// after here doc redis
static int ms_expand_all_vars(t_token **tkns)
{
	t_token	*current;
	t_token	*prev_token;

	current = *tkns;
	prev_token = NULL;
	while (current)
	{
		if(!ms_expand_var(current, prev_token))
			return false;
		prev_token = current;
		current = current->next;
	}
	return 0;
}

static void ms_expand_all_quotes(t_token **tokns)
{
	t_token *current;
	t_token	*prev_token;

	current = *tokns;
	prev_token = NULL;
	while (current)
	{
		if (current->kind == T_WORD && (prev_token == NULL
				|| prev_token->kind != T_HERE_DOC))
			current->value = ms_quote_show(remove_quote(current->value));
		prev_token = current;
		current = current->next;
	}
}

void	ms_expand(t_token **tkns)
{
	if(tkns == NULL)
		return;
	ms_expand_all_vars(tkns);
	del_empty_token(tkns);
	ms_expand_all_quotes(tkns);
}
