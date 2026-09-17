/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:23:48 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:23:53 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_cmd_t.h"
#include "ms_redi.h"
#include <libft_arr.h>
#include <libft_mem.h>

void	ms_cmd_free(t_ms_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))ms_redi_free);
	ft_arr_each((t_arr)(cmd->argv), (void (*)(t_arr_el))ft_free);
	ft_free(cmd->reds);
	ft_free(cmd->argv);
	ft_free(cmd);
}
