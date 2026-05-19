/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_op_t.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:04:07 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 19:04:08 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_CMD_T_H
# define MS_CMD_T_H
# include <libft_byte_t.h>
# include <stddef.h>

typedef struct s_ms_redi
{
	enum		e_ms_redi_kind
	{
		INVALID = -1,
		IN,
		OUT,
		OUT_APPEND,
		HERE_DOC
	} kind;
	enum		e_ms_redi_source
	{
		FD,
		PATH
	} source_kind;
	union		u_redi_source
	{
		char	*path;
		int		fd;
	} source;
}				t_ms_redi;

typedef struct s_ms_cmd
{
	char		**argv;
	t_ms_redi	**reds;
}				t_ms_cmd;

void			ms_cmd_free(t_ms_cmd *cmd);

#endif
