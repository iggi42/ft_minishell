/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 13:41:00 by fkruger           #+#    #+#             */
/*   Updated: 2026/07/26 13:42:22 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_arr.h"
#include "libft_iol.h"
#include "libft_ll.h"
#include "libft_mem.h"
#include "libft_str.h"

// void			ft_iol_append(t_iol *io_l, char *start, size_t size);
// TODO WRITE TESTS
char	*ft_join_arr(char **s, char *sep)
{
	t_iol		result;
	t_iol_el	iol_sep;
	char		*str_result;
	size_t		i;

	i = 1;
	if (s == NULL)
		return (NULL);
	result = NULL;
	if (s[0])
		ft_iol_append(&result, s[0], ft_strlen(s[0]));
	iol_sep.free = NULL;
	iol_sep.size = ft_strlen(sep);
	iol_sep.buffer = sep;
	while (s && i < ft_arr_len((t_arr)s))
		ft_iol_append(&result, s[i], ft_strlen(s[i]));
	str_result = ft_iol_str(result);
	ft_iol_del(&result);
	return (str_result);
}
