/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_cache.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:58:42 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/23 17:58:42 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FD_CACHE_H
# define FD_CACHE_H

# include <stddef.h>

void	*fdc_add(int fd, void *buffer);
void	*fdc_pop(int fd, void *(fallback)(size_t size), size_t new_size);

void	fdc_cleanup(void);

#endif
