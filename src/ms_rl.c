#include "libft_io.h"
#include "ms_signal.h"
#include <stdio.h>
#include "readline/readline.h"
#include <unistd.h>
#include <signal.h>

static int	ms_rl_event_hook(void)
{
	int	sig;

	sig = ms_signal_consume();
	if (sig == SIGINT)
	{
		(void) write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	// else
	// 	ft_printf_fd(STDERR_FILENO, "ms_rl_event_hook consumed: [%d]\n", sig);
	return (0);
}

char	*ms_repl_rl_wrapper(char *prompt)
{
	rl_event_hook = ms_rl_event_hook;
	return (readline(prompt));
}
