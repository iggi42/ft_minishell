/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 16:07:52 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/19 16:07:57 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// tells an empty line apart from a line that failed to tokenize
int	ms_line_is_blank(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	return (input[i] == '\0');
}
