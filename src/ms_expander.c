#include "ms_parsing.h"
#include "ms_token.h"
#include "ms_env.h"
#include "ms_dbg.h"
#include <stdbool.h>
#include <libft_mem.h>

// // we know the curent->next is not NULL and a word
// if (is_ambigous_redi(current->next->value))
// 	return (ms_protect(ft_strf(ambi_error_msg, current->next->value)));
// // check if the next word expands to anything here, if it does not
// // it should an ambigious redirect, I think?
static void ms_expand_var(t_token *word)
{
	ms_expand_str(&word->value, true);
	ft_printf("new val: %s \n", word->value);
	ms_print_tokens(ms_tokenize(word->value));
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
			ms_expand_var(current);
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
int	ms_expand(t_token **tkns)
{
	int result;

	if(tkns == NULL)
		return 1;
	result = 0;
	ms_expand_all_vars(tkns);
	result |= del_empty_token(tkns);
	ms_expand_all_quotes(tkns);
	return result;
}
