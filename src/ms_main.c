/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:51:50 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 18:51:53 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_repl.h"
#include <libft_io.h>
#include <unistd.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{
	if (argc != 1)
		return ((void)argv, -1);
	ms_load_env(__environ);
	ms_repl();
	clear_history();
	ms_env_free();
	ft_gnl(-1);
}
