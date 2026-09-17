/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:25:15 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 12:25:17 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_exit.h"
#include "ms_signal.h"
#include <libft_io.h>
#include <signal.h>

static int	*last_signal_store(void)
{
	static int	last_signal;

	return (&last_signal);
}

int	ms_signal_last(void)
{
	return (*last_signal_store());
}

void	ms_signal_listen(int sig)
{
	*last_signal_store() = sig;
	if (sig != 0)
		ms_env_set_status(128 + sig);
}

void	ms_signal_init(void)
{
	ms_signal_set_handler(-1, NULL);
	ms_signal_set_handler(SIGINT, ms_signal_listen);
	ms_signal_set_handler(SIGQUIT, ms_signal_listen);
	ms_signal_set_handler(SIGPIPE, ms_signal_exit);
}

void	ms_signal_child(void)
{
	ms_signal_set_handler(SIGINT, ms_signal_exit);
	ms_signal_set_handler(SIGQUIT, ms_signal_exit);
}
