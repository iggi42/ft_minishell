/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:35:10 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/23 13:35:11 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_io_opts.h>
#include <libft_iol.h>
#include <libft_str.h>
#include <libft_kv.h>
#include "fd_cache.h"

static void gnl_cleanup(t_kv *caches)
{
	ft_kv_free(caches);
}

char	*ft_gnl(int fd)
{
	if(fd < 0)
		return (NULL);
	char *buffer = fdc_at(fd);

	return NULL;
}
