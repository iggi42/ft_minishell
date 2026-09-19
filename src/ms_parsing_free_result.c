/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_free_result.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:10:20 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 12:10:26 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parsing.h"
#include <libft_arr.h>
#include <libft_mem.h>

void	ms_free_parser_result(t_ms_parse_res *parsing_result, char *line)
{
	ft_free(line);
	if (parsing_result == NULL)
		return ;
	if (parsing_result->exit_code == 0)
		ft_arr_each((t_arr)parsing_result->source.cmds,
			(void (*)(t_arr_el))ms_cmd_free);
	ft_free(parsing_result->source.error_msg);
	ft_free(parsing_result);
}
