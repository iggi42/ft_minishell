/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:32:12 by fkruger           #+#    #+#             */
/*   Updated: 2026/07/26 17:32:14 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_arr.h"
#include "libft_mem.h"
#include "libft_str.h"

static void	*add_el_len(void *acc, t_arr_el el)
{
	*((size_t *)acc) += ft_strlen((char *)el);
	return (acc);
}

// TODO WRITE TESTS
char	*ft_join(char **s, char *sep)
{
	size_t	result_len;
	size_t	input_len;
	size_t	i;
	char	*result;

	if (s == NULL)
		return (NULL);
	input_len = ft_arr_len((t_arr)s);
	if (input_len == 0)
		return (ft_strdup(""));
	i = ft_strlen(s[0]);
	result_len = ft_strlen(sep) * (input_len - 1);
	ft_arr_fold((t_arr)s, add_el_len, &result_len);
	result = ft_str_alloc(result_len);
	if (!result)
		return (NULL);
	ft_memmove(result, s[0], i);
	while (*s && i <= result_len)
	{
		ft_memmove(result + i, *s, ft_strlen(*s));
		s++;
	}
	return (result);
}
