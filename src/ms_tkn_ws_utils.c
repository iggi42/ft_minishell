/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tkn_ws_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:28:07 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/19 15:28:49 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include <libft_str.h>

bool	ms_ws_is_in_ifs(char c)
{
	return (ft_strchr(ms_env_get("IFS", " \t\n"), c) != NULL);
}

bool	ms_ws_is_quote(char c)
{
	return (('\"' == c) || ('\'' == c));
}
