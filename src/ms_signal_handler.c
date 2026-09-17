#include <libft_byte_t.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft_io.h"
#include "ms_signal.h"

volatile sig_atomic_t	g_ms_signal;

static void ms_real_sh(int sig)
{
	g_ms_signal = sig;
}

static ms_sig_handler	*ms_sig_store(t_byte sig)
{
	static ms_sig_handler	store[sizeof(t_byte)];

	return (&store[sig]);
}

static void	ms_sig_trigger(t_byte sig)
{
	if (*ms_sig_store(sig) != NULL)
		(*ms_sig_store(sig))(sig);
}

void	ms_signal_set_handler(int sig, ms_sig_handler dab)
{
	static struct sigaction	s_sig;

	if(sig < 0)
	{
		sigemptyset(&s_sig.sa_mask);
		s_sig.sa_handler = ms_real_sh;
		s_sig.sa_flags = 0;
	}
	*ms_sig_store(sig) = dab;
	if(dab == NULL)
		signal(sig, SIG_DFL);
	else
		sigaction(sig, &s_sig, NULL);
}

int	ms_signal_consume(void)
{
	int	sig;

	sig = g_ms_signal;
	if(sig == 0)
		return 0;
	g_ms_signal = 0;
	ms_sig_trigger(sig);
	return (sig);
}

