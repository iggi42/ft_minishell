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
#include <libft_io.h>

int	main()
{
	char *get0 = ms_get_env("USER", "{{unset}}");
	ms_set_env("USER", "homer");
	char *get1 = ms_get_env("USER", "{{unset}}");
	ft_printf("[%s] ==> [%s]\n", get0, get1);
	ms_env_free();
	return (-1);
}
