/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iol_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_iol.h"

char	*ft_iol_str(t_list *iol_l)
{
	size_t	len;
	char	*s;

	len = ft_iol_size(iol_l);
	s = ft_str_alloc(len);
	if (len <= ft_iol_str_l(iol_l, s, len))
		return (s);
	ft_free(s);
	return (NULL);
}
