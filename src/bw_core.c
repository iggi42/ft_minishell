/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 05:37:35 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/07 05:37:35 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bw.h"
#include "bw_priv_t.h"
#include "utils.h"
#include <libft_mem.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static t_ms	**head(void)
{
	static t_ms	*core_head;

	return (&core_head);
}

void	ft_bw_add(int fd)
{
	t_ms	*new_head;

	if (fd < 2)
		return ;
	new_head = my_malloc(sizeof(t_ms));
	new_head->next = *head();
	new_head->fd = fd;
	*head() = new_head;
}

void	ft_bw_rm(int fd)
{
	t_ms	**curr;
	t_ms	*cache;

	if (fd < 0)
		return ;
	curr = head();
	while (*curr)
	{
		if ((*curr)->fd == fd)
		{
			cache = *curr;
			*curr = (*curr)->next;
			ft_free(cache);
		}
		else
			curr = &(*curr)->next;
	}
}

void	ft_bw_each(void (*apply)(int fd))
{
	t_ms	*curr;

	curr = *head();
	while (curr)
		curr = (apply(curr->fd), curr->next);
}

void	ft_bw_cleanup(void)
{
	t_ms	*curr;
	t_ms	*cache;

	curr = *head();
	while (curr)
	{
		if (curr->fd > 2)
			close(curr->fd);
		cache = curr;
		curr = curr->next;
		ft_free(cache);
	}
	*head() = NULL;
}
