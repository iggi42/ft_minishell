
#include <signal.h>

extern volatile sig_atomic_t	g_ms_signal;

void							ms_signal_init(void);
void							ms_signal_child(void);
int								ms_signal_consume(void);
