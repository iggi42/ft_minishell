
#include "ms_env.h"
#include <unistd.h>

// this logic describes what prompt you see in interactive mode

char	*ms_repl_prompt_shell(void)
{
	if (isatty(STDIN_FILENO) == 0)
		return "";
	return (ms_env_get("PS1", "minishell %> "));
}

char	*ms_repl_prompt_heredoc(void)
{
	if (isatty(STDIN_FILENO) == 0)
		return "";
	return (ms_env_get("PS2", "minishell_heredoc %> "));
}
