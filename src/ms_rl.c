#include "ms_signal.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

static int	ms_rl_event_hook(void)
{
	int	sig;

	sig = ms_signal_consume();
	if (sig == SIGINT)
	{
		(void)write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return (0);
}

char	*ms_repl_rl_wrapper(char *prompt)
{
	char	*result;

	rl_event_hook = ms_rl_event_hook;
	result = readline(prompt);
	// rl_event_hook = NULL;
	return (result);
}
