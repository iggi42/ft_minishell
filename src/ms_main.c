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
#include "ms_token.h"
#include "ms_utils.h"
#include <libft_io.h>
#include <libft_mem.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	if (argc != 1)
		return ((void)argv, -1);
	ms_load_env(__environ);
	ms_repl();
	ms_env_free();
}
