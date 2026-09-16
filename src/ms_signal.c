// #include "ms_exit.h"
#include "ms_exit.h"
#include "ms_signal.h"
#include <signal.h>
#include <libft_io.h>

void ms_signal_exit(int sig)
{
	ms_exit(128 + sig);
}

void ms_signal_void(int sig)
{
	(void) sig;
}

void	ms_signal_init(void)
{
	ms_signal_set_handler(-1, NULL);
	ms_signal_set_handler(SIGINT, ms_signal_void);
	ms_signal_set_handler(SIGPIPE, ms_signal_exit);
	ms_signal_set_handler(SIGQUIT, ms_signal_exit);
}

void	ms_signal_child(void)
{
	ms_signal_set_handler(SIGINT, ms_signal_exit);
}
