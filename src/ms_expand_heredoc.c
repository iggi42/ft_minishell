#include "libft_mem.h"
#include "libft_str.h"
#include "ms_env.h"
#include "ms_safe.h"
#include "ms_parsing_getlen.h"
#include <libft_arr.h>
#include <stddef.h>

static size_t	count_dollars(char *str)
{
	size_t	dollars;

	dollars = 0;
	while (42)
	{
		str = ft_strchr(str, '$');
		if (str == NULL)
			break ;
		dollars++;
	}
	return (dollars);
}

static char	*ms_expand_plain_var_iter(char **rest)
{
	size_t	el_size;
	char *var_name;
	char *result;

	if (*rest == NULL || **rest == '\0')
		return (NULL);
	el_size = 0;
	result = NULL;
	if (**rest == '$')
	{
		el_size = ms_parsing_varname((*rest) + 1);
		if(el_size > 0)
		{
			var_name = ms_substr(*rest, 1, el_size);
			result = ms_strdup(ms_env_get(var_name, ""));
			(*rest) += el_size;
			ft_free(var_name);
		}
		else
		{
			result = ms_strdup("$");
			(*rest) += 1;
		}
	}
	else
	{
		var_name = 
		el_size = 
	}
	
}

char	*ms_expand_heredoc_line(char *str)
{
	char	*iter_state;
	char	**parts;

	parts = ft_arr_from_iter((ft_iter)ms_expand_plain_var_iter, &iter_state);
}
