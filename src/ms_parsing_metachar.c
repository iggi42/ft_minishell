#include <libft_str.h>

bool	ms_is_metachar(char c)
{
	return (ft_strchr("|&;()<> \t\n", c) != NULL);
}
