/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:12:49 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:12:50 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSING_UTILS_H
# define MS_PARSING_UTILS_H
# include "ms_cmd_t.h"

t_ms_redi	*redi_builder(char *redi_path, int kind);

#endif
