
#include <stddef.h>
#include <libft_char.h>

size_t	ms_parsing_varname(char *str)
{
	int	len;

	len = 0;
	if (str[len] == '?')
		return (1);
	if (str[len] && (ft_isalpha(str[len]) || str[len] == '_'))
		len++;
	else
		return (0);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}
