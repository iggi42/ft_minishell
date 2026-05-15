/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_fmt.h"
#include "libft_iol.h"

int	ft_printf_fd(int fd, const char *template, ...)
{
	t_list	*seg_list;
	int		result;
	va_list	args;

	seg_list = ft_fmt_parse((char *)template);
	va_start(args, template);
	ft_fmt_apply(seg_list, &args);
	va_end(args);
	result = ft_iol_write(seg_list, fd);
	ft_iol_del(&seg_list);
	return (result);
}
