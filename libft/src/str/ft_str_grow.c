#include <stddef.h>
#include <libft_str.h>
#include <libft_mem.h>
#include <libft_io.h>

char *ft_str_grow(char **input, size_t len)
{
	char *old = *input;
	size_t old_len = ft_strlen(old);

	if (len <= old_len)
		return (NULL);
	*input = ft_str_alloc(len);
	if(input != NULL)
	{
		if(len <= ft_strlcpy(*input, old, len))
			return (ft_write(2, "WTF", 3), NULL);
	}
	ft_free(old);
	return *input;
}
