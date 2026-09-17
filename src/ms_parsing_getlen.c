/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_getlen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:02:06 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 12:02:12 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft_char.h>

size_t	ms_parsing_varname(char *str)
{
	int	len;

	len = 0;
	if (str[len] == '?')
		return (1);
	if (str[len] && (ft_isalpha(str[len]) || str[len] == '_'))
		len++;
	else
		return (0);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}
