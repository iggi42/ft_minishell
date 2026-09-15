#include "ms_exit.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <libft_io.h>
#include <unistd.h>

volatile sig_atomic_t g_ms_signal;

static void ms_sig_handler(int sig)
{
	g_ms_signal = sig;
}

int ms_signal_consume(void)
{
	int sig;

	sig = g_ms_signal;
	g_ms_signal = 0;
	return sig;
}

void ms_signal_init(void)
{
	struct sigaction s_sig;

	sigemptyset(&s_sig.sa_mask);
	s_sig.sa_handler = ms_sig_handler;
	s_sig.sa_flags = 0;
	sigaction(SIGINT, &s_sig, NULL);
	sigaction(SIGQUIT, &s_sig, NULL);
}

void ms_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

