#include "ms_repl.h"
#include <stddef.h>
#include <libft_io.h>
#include <unistd.h>

static char	*ms_cut_nl(char *s)
{
	size_t	i;

	i = 0;
	while (s != NULL && s[i] != '\0')
	{
		if (s[i] == '\n' && s[i + 1] == '\0')
			s[i] = '\0';
		i++;
	}
	return (s);
}

char	*ms_repl_gnl(ms_repl_prompt_get prompt_getter, int (*ms_rl_hook)(void))
{
	if (!isatty(STDIN_FILENO))
		return (ms_cut_nl(ft_gnl(STDIN_FILENO)));
	return ms_repl_rl_wrapper(prompt_getter, ms_rl_hook);
}
