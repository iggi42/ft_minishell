/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:51:50 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/18 15:41:22 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_exec_utils.h"
#include "ms_exit.h"
#include "ms_repl.h"
#include "ms_signal.h"
#include <libft_io.h>

int	main(int argc, char **argv)
{
	if (argc != 1)
		return ((void)argv, -1);
	ms_signal_init();
	ms_env_init();
	ms_repl();
	ms_repl_history_clear();
	ms_env_free();
	ft_gnl(-1);
	ms_stdenv_close();
	// uncomment this for the eval to make garabage collector run and the very end
	// we tested without them cleaning up and the end if we return to main (doing an exit)
	// ms_exit(ms_env_get_status());
	return (ms_env_get_status());
}
