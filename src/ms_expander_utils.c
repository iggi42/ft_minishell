#include "ms_token.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

int	unquote_len(char *str)
{
	int		i;
	int		len;
	bool	single_q;
	bool	double_q;

	i = 0;
	len = 0;
	single_q = false;
	double_q = false;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[i] == '\"' && !single_q)
			double_q = !double_q;
		else
			len++;
	}
	return (len);
}

void	unquote_cpy(char *str, char *new_str)
{
	int		i;
	int		j;
	bool	single_q;
	bool	double_q;

	i = 0;
	j = 0;
	single_q = false;
	double_q = false;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[i] == '\"' && !single_q)
			double_q = !double_q;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = 0;	
}

char	*remove_quote(char *str)
{
	char	*new_str;

	if (!str)
		return(NULL);
	new_str = malloc(unquote_len(str) + 1);
	if (!new_str)
		return NULL;
	unquote_cpy(str, new_str);
	free(str);
	return (new_str);
}

t_token	*remove_token(t_token **list, t_token *previous, t_token *current)
{
	t_token	*next_token;

	next_token = current->next;
	if (previous)
		previous->next = next_token;
	else
		*list = next_token;
	free(current->value);
	free(current);
	return next_token;
}

void	del_empty_token(t_token **list)
{
	t_token	*current;
	t_token	*previous;

	current = *list;
	previous = NULL;
	while (current)
	{
		if (current->kind == WORD && current->value[0] == 0)
			current = remove_token(list, previous, current);
		else
		{
			previous = current;
			current = current->next;
		}
	}
}
