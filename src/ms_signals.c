#include <readline/readline.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <libft_io.h>
#include "ms_exit.h"

volatile sig_atomic_t g_ms_signal;

static void ms_sig_handler(int sig)
{
	g_ms_signal = sig;
}

void ms_signal_init(void)
{
	struct sigaction s_sig;

	rl_catch_signals = 0;
	s_sig.sa_handler = ms_sig_handler;
	sigemptyset(&s_sig.sa_mask);
	s_sig.sa_flags = 0;
	sigaction(SIGINT, &s_sig, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void ms_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ms_signal_hook(void)
{
	if(g_ms_signal == SIGINT)
	{
		ft_printf("found signal %d\n", g_ms_signal);
		g_ms_signal = 0;
		rl_done = 1;
	}
}

