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

#include "kg_priv_t.h"
#include "ms_safe.h"
#include <libft_os.h>
#include <libft_mem.h>
#include <stdbool.h>

static t_kg_el	**head(void)
{
	static t_kg_el	*core_head;

	return (&core_head);
}

void	kg_add(pid_t new_pid)
{
	t_kg_el	*new_head;

	if (new_pid < 1)
		return ;
	// TODO wait for new_pid even if this fails
	new_head = ms_malloc(sizeof(t_kg_el));
	new_head->next = *head();
	new_head->pid = new_pid;
	*head() = new_head;
}

bool	kg_rm(pid_t pid)
{
	t_kg_el	**curr;
	t_kg_el	*cache;
	bool	result;

	if (pid  < 1)
		return false;
	result = false;
	curr = head();
	while (*curr)
	{
		if ((*curr)->pid == pid)
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

void	kg_each(void (*apply)(pid_t stored_pid))
{
	t_kg_el	*curr;

	curr = *head();
	while (curr)
		curr = (apply(curr->pid), curr->next);
}

void	kg_cleanup(bool wait)
{
	t_kg_el	*curr;
	t_kg_el	*cache;

	curr = *head();
	while (curr)
	{
		if(wait)
			ft_wait(curr->pid);
		cache = curr;
		curr = curr->next;
		ft_free(cache);
	}
	*head() = NULL;
}
