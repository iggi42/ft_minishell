#include "libft_kv.h"
#include "ms_token.h"
#include "ms_env.h"
#include "ms_dbg.h"
#include <libft_str.h>
#include <libft_char.h>
#include <stdbool.h>
#include <stdlib.h>

int		get_len(char *str)
{
	int	len;
	
	len = 0;
	if (str[len] == '?')
		return (len);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
			len++;
	return (len);
}

char	*slice_and_dice(char *str, int start, int len, char *var)
{
	char	*before;
	char	*after;
	char	*tmp;
	char	*new_str;

	before = ft_substr(str, 0, start);
	after = ft_substr(str, start + len, ft_strlen(str) - (start + len));
	tmp = ft_strjoin(before, var);
	new_str = ft_strjoin(tmp, after);
	free(before);
	free(after);
	free(tmp);
	free(str);
	return (new_str);
}

char	*expand(char *str, int *i)
{
	char	*var_name;
	char	*env_var;
	char	*new_str;
	int		len;

	len = get_len(str + *i + 1);
	if (len == 0)
	{
		(*i)++;
		return (str);
	}
	var_name = ft_substr(str, *i + 1, len);
	if (var_name[0] == '?')
		env_var = "";		//TODO: get prev exit code
	else
		env_var = ms_get_env(var_name, "");
	new_str = slice_and_dice(str, *i, len + 1, env_var);
	*i = *i + ft_strlen(env_var);
	free(var_name);
	return (new_str);
}

char	*expand_var(char *str)
{
	int		i;
	bool	single_q;
	bool	double_q;

	i = 0;
	single_q = false;
	double_q = false;
	while (str[i])
	{
		if (str[i] == '\'' && double_q == false)
			single_q = !single_q;
		else if (str[i] == '\"' && single_q == false)
			double_q = !double_q;
		else if (str[i] == '$')
		{
			if (single_q == true)
			 i++;
			else
			{
				str = expand(str, &i);
				continue;
			}
		}
		i++;
	}
	return (str);
}

void	ms_expand(t_token **list)
{
	t_token	*current;

	current = *list;
	while (current)
	{
		if (current->kind == T_WORD)
			current->value = expand_var(current->value);
		current = current->next;
	}
	del_empty_token(list);
	current = *list;
	while (current)
	{
		if (current->kind == T_WORD)
			current->value = remove_quote(current->value);
		current = current->next;
	}
	ms_print_tokens(*list);
}
