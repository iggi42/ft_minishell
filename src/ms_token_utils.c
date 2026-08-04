#include "ms_token.h"
#include <stdlib.h>

t_token	*new_token(char *value, enum e_token_type kind)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = value;
	node->kind = kind;
	node->next = NULL;
	return (node);
}

void	append_token(t_token **list, char *value, enum e_token_type kind)
{
	t_token	*new_node;
	t_token	*current;

	if (!list || !value)
		return ;
	new_node = new_token(value, kind);
	if (!new_node)
	{
		free(value);
		return ;
	}
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

t_token	*free_token_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free_token(list);
		list = tmp;
	}
	return (NULL);
}
