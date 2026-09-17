/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:04:10 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 19:04:12 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSING_H
# define MS_PARSING_H
# include "ms_cmd_t.h"
# include <libft_kv.h>
# include <stdbool.h>

typedef struct s_ms_parse_res
{
	bool			success;
	union			u_ms_parse_res_body
	{
		char		*error_msg;
		t_ms_cmd	**cmds;
	} source;
}					t_ms_parse_res;

void				ms_free_parser_result(t_ms_parse_res *res, char *line);

t_ms_parse_res		*ms_parse(char *input);

// returns always a freeable string
// char				*ms_expand_var(char *text_with_vars);
void				ms_expand_var(char **str, bool care_about_quotes);

bool				ms_is_metachar(char c);

#endif
