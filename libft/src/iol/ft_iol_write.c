/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iol_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_io.h"
#include "libft_iol.h"

// TODO change return type to a much larger number
ssize_t	ft_iol_write(t_list *l, int fd)
{
	t_iol_el	*el;
	size_t		result;
	int			write_code;

	result = 0;
	while (l != NULL)
	{
		el = (t_iol_el *)l->content;
		write_code = ft_write(fd, el->buffer, el->size);
		if (write_code < 0)
			return (write_code);
		result += write_code;
		l = l->next;
	}
	return (result);
}
