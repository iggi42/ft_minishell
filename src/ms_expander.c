#include "ms_parsing.h"
#include "ms_token.h"
#include "ms_dbg.h"
#include <stdbool.h>
#include <libft_mem.h>
#include <stdio.h>

// returns the last token from the resulting expansion
static t_token *ms_expand_var(t_token **word)
{
	if(word == NULL)
		return NULL;
	ms_expand_str(&((*word)->value), true);
	return ms_word_split(word);
}

// this function name is a lie, we don't expand the tokens
// after here doc redis
static void ms_expand_all_vars(t_token **tkns)
{
	t_token	*current;
	t_token	*prev_token;

	current = *tkns;
	prev_token = NULL;
	while (current)
	{
		if (current->kind == T_WORD && prev_token != NULL
			&& prev_token->kind != T_HERE_DOC)
			current = ms_expand_var(&(prev_token->next));
		prev_token = current;
		current = current->next;
	}	current = *tkns;
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

// 0 => expanding encountered issues
// 1 => expanding worked out
int	ms_expand(t_token **tkns, char **err_msg)
{
	int result;

	if(tkns == NULL)
		return 1;
	result = 0;
	ms_expand_all_vars(tkns);
	result |= del_empty_token(tkns, err_msg);
	ms_expand_all_quotes(tkns);
	return result;
}
