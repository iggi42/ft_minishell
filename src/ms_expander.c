#include "ms_env.h"
#include "ms_exit.h"
#include "ms_parsing_getlen.h"
#include "ms_safe.h"
#include "ms_token.h"
#include "unistd.h"
#include <libft_mem.h>
#include <libft_str.h>
#include <libft_io.h>


// 
static char	*slice_and_dice(char *str, size_t start, size_t len, char *var)
{
	char	*before;
	char	*after;
	char	*tmp;
	char	*new_str;

	before = ms_substr(str, 0, start);
	after = ms_substr(str, start + len, ft_strlen(str) - (start + len));
	tmp = ms_protect(ft_strjoin(before, var));
	new_str = ms_protect(ft_strjoin(tmp, after));
	ft_free(before);
	ft_free(after);
	ft_free(tmp);
	ft_free(str);
	return (new_str);
}

char	*expand(char *str, int *i)
{
	char	*var_name;
	char	*env_var;
	char	*new_str;
	int		len;

	len = ms_parsing_varname(str + *i + 1);
	if (len == 0)
	{
		(*i)++;
		return (str);
	}
	var_name = ms_substr(str, *i + 1, len);
	env_var = ms_env_get(var_name, var_name);
	new_str = slice_and_dice(str, *i, len + 1, env_var);
	*i = *i + ft_strlen(env_var);
	ft_free(var_name);
	return (new_str);
}

char	*ms_expand_var(char *str, bool care_about_quotes)
{
	int		i;
	bool	single_q;
	bool	double_q;

	i = 0;
	single_q = false;
	double_q = false;
	while (str[i])
	{
		if (care_about_quotes && str[i] == '\'' && double_q == false)
			single_q = !single_q;
		else if (care_about_quotes && str[i] == '\"' && single_q == false)
			double_q = !double_q;
		else if (str[i] == '$')
		{
			if ((care_about_quotes && single_q == true) || str[i + 1] == '\0')
				break;
			else
			{
				str = expand(str, &i);
				continue ;
			}
		}
		i++;
	}
	return (str);
}

void	ms_expand(t_token **list)
{
	t_token	*current;
	t_token *prev_token;

	current = *list;
	prev_token = NULL;
	while (current)
	{
		if (current->kind == T_WORD && prev_token != NULL && prev_token->kind != T_HERE_DOC )
			current->value = ms_expand_var(current->value, true);
		prev_token = current;
		current = current->next;
	}
	del_empty_token(list);
	current = *list;
	prev_token = NULL;
	while (current)
	{
		if (current->kind == T_WORD && prev_token != NULL && prev_token->kind != T_HERE_DOC)
			current->value = remove_quote(current->value);
		prev_token = current;
		current = current->next;
	}
}
