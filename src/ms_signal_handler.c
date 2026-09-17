/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:58:43 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:58:51 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_signal.h"
#include <libft_byte_t.h>
#include <libft_io.h>
#include <signal.h>

volatile sig_atomic_t	g_ms_signal;

static void	ms_real_sh(int sig)
{
	g_ms_signal = sig;
}

static t_ms_sig_handler	*ms_sig_store(t_byte sig)
{
	static t_ms_sig_handler	store[MS_SIG_SLOTS];

	return (&store[sig]);
}

static void	ms_sig_trigger(t_byte sig)
{
	if (*ms_sig_store(sig) != NULL)
		(*ms_sig_store(sig))(sig);
}

void	ms_signal_set_handler(int sig, t_ms_sig_handler dab)
{
	static struct sigaction	s_sig;

	if (sig < 0)
	{
		sigemptyset(&s_sig.sa_mask);
		s_sig.sa_handler = ms_real_sh;
		s_sig.sa_flags = 0;
		return ;
	}
	*ms_sig_store(sig) = dab;
	if (dab == NULL)
		signal(sig, SIG_DFL);
	else
		sigaction(sig, &s_sig, NULL);
}

int	ms_signal_consume(void)
{
	int	sig;

	sig = g_ms_signal;
	if (sig == 0)
		return (0);
	g_ms_signal = 0;
	ms_sig_trigger(sig);
	return (sig);
}
