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
#include "ms_exit.h"
#include "ms_safe.h"
#include <libft_mem.h>
#include <stdbool.h>
#include <unistd.h>

static t_bw_el	**head(void)
{
	static t_bw_el	*core_head;

	return (&core_head);
}

void	ft_bw_add(int new_fd)
{
	t_bw_el	*new_head;

	if (new_fd < 2)
		return ;
	// TODO close new_fd even if this fails
	new_head = ft_malloc(sizeof(t_bw_el));
	if (new_head == NULL)
	{
		close(new_fd);
		ms_protect(NULL);
	}
	new_head->next = *head();
	new_head->fd = new_fd;
	*head() = new_head;
}

bool	ft_bw_rm(int fd)
{
	t_bw_el	**curr;
	t_bw_el	*cache;
	bool	result;

	if (fd < 2)
		return (false);
	result = false;
	curr = head();
	while (*curr)
	{
		if ((*curr)->fd == fd)
		{
			result = true;
			cache = *curr;
			*curr = (*curr)->next;
			ft_free(cache);
		}
		else
			curr = &(*curr)->next;
	}
	return (result);
}

void	ft_bw_each(void (*apply)(int fd))
{
	t_bw_el	*curr;

	curr = *head();
	while (curr)
		curr = (apply(curr->fd), curr->next);
}

void	ft_bw_cleanup(void)
{
	t_bw_el	*curr;
	t_bw_el	*cache;

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
