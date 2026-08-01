/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_apply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_fmt_ops.h"
#include <stdarg.h>

static void	replace_op(t_iol_el *el, va_list *args)
{
	char	type;

	if (el->size < 2 || *(el->buffer) != '%')
		return ;
	type = *(el->buffer + 1);
	if (type == '%')
		el->size = sizeof(char);
	else if (type == 's')
		ft_fmt_set_str(el, va_arg(*args, char *));
	else if (type == 'c')
		ft_fmt_set_c(el, (char)va_arg(*args, int));
	else if (type == 'p')
		ft_fmt_set_ptr(el, (void *)va_arg(*args, void *));
	else if (type == 'i')
		ft_fmt_set_i(el, (int) va_arg(*args, int));
	else if (type == 'l' || type == 'd')
		ft_fmt_set_l(el, (long) va_arg(*args, long));
	else if (type == 'u')
		ft_fmt_set_ui(el, (unsigned int)va_arg(*args, unsigned int));
	else if (type == 'x' || type == 'X')
		ft_fmt_set_hex(el, (unsigned int)va_arg(*args, unsigned int));
}

void	ft_fmt_apply(t_list *io_list, va_list *args)
{
	if (io_list == NULL)
		return ;
	replace_op(io_list->content, args);
	ft_fmt_apply(io_list->next, args);
}
