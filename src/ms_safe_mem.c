// put protected calls for memory allocation here, ms_malloc, ms_strdup, etc

#include "ms_exit.h"
#include <errno.h>
#include <libft_mem.h>
#include <libft_str.h>

void	*ms_protect(void *cond)
{
	return (ms_exit_if(cond, MS_MEM_ERR));
}

void	*ms_malloc(size_t size)
{
	void	*result;

	errno = 0;
	result = ft_malloc(size);
	if (result)
		return (result);
	ms_error_out(EXIT_FAILURE, NULL, errno);
	return (NULL);
}

char	*ms_strdup(char *copy_me)
{
	return ms_protect(ft_strdup(copy_me));
}

char	*ms_substr(const char *s, size_t start, size_t len)
{
	return ms_protect(ft_substr(s, start, len));
}
