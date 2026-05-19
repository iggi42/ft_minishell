/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:04:07 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 19:04:08 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_H
# define MS_EXEC_H
# include <libft_byte_t.h>
# include "ms_cmd_t.h"

t_byte			ms_run_pipe(t_ms_cmd **full_pipe);
#endif
