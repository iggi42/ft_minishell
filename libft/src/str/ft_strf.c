/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:35:38 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_iol.h"
#include "libft_fmt.h"
#include <stdarg.h>

char	*ft_strf(const char *template, ...)
{
	t_list	*seg_list;
	char	*result;
	va_list	args;

	seg_list = ft_fmt_parse((char *)template);
	va_start(args, template);
	ft_fmt_apply(seg_list, &args);
	result = ft_iol_str(seg_list);
	ft_iol_del(&seg_list);
	va_end(args);
	return (result);
}
