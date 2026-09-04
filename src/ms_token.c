#include "../inc/ms_token.h"
#include <cstdio>
#include <stdlib.h>

int	handle_operator(char *str, int i, t_token **tokens)
{
	enum e_token_type	type;
	char				*operator;
	int					len;

	len = 1;
	if (str[i] == '>' && str[i + 1] == '>')
	{
		len = 2;
		type = T_OUT_APPEND;
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		len = 2;
		type = T_HERE_DOC;
	}
	else if (str[i] == '>')
		type = T_OUT;
	else if (str[i] == '<')
		type = T_IN;
	else if (str[i] == '|')
		type = PIPE;
	else
		return 0;
	operator = ft_substr(str, i, len);
	append_token(tokens, operator, type);
	return (i + len);
}

int	handle_arg(char *str, int i, t_token **tokens)
{
	int		start;
	char	quote;

	start = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|'
	       && str[i] != '<' && str[i] != '>')
	{
		if (str [i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == '\0')
				return (-1);
			i++;
		}
		else
			i++;
	}
	append_token(tokens, ft_substr(str, start, i - start), WORD);
	return (i);
}

int		validate(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current && current->kind == PIPE)
		return (printf("minishell: syntax error near unexpected sign '|'\n"), 0);
	while (current)
	{
		if (is_redirect(current->kind))
		{
			if (!current->next || current->next->kind != WORD)
				return (printf("minishell: syntax error near unexpected sign 'newline'\n"), 0);
		}
		if (current->kind == PIPE)
		{
			if (!current->next || current->next->kind == PIPE)
				return (printf("minishell: syntax error near unexpected sign '|'\n"));
		}
		current = current->next;
	}
	return (1);
}

t_token	*ms_tokenize(char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;

	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i = handle_operator(input, i, &tokens);
		else
		{
			i = handle_arg(input, i, &tokens);
			if (i == -1)
				return (NULL);	//TODO: free token list function? print smth?
		}
	}
	return (tokens);
}
