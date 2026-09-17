

typedef void	(*ms_sig_handler)(int);

void			ms_signal_init(void);
void			ms_signal_child(void);

void			ms_signal_listen(int sig);
int				ms_signal_last(void);
void			ms_signal_set_handler(int sig, ms_sig_handler dab);
int				ms_signal_consume(void);
