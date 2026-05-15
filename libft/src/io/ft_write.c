/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:35:38 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

ssize_t	ft_write(int fd, const void *buf, size_t n)
{
	ssize_t	write_code;
	size_t	written_bytes;

	written_bytes = 0;
	while (n > written_bytes)
	{
		write_code = write(fd, buf + written_bytes, n - written_bytes);
		if (write_code < 0)
			return (write_code);
		written_bytes += write_code;
	}
	return (written_bytes);
}
