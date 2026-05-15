/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m3_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 05:37:35 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/07 05:37:35 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_merle.h"
#include "m3_priv.h"
#include <stdbool.h>
#include <stdlib.h>

static t_ms	**head(void)
{
	static t_ms	*core_head;

	return (&core_head);
}

bool	ft_m3_add(void *ptr)
{
	t_ms	*new_head;

	if (ptr == NULL)
		return (false);
	new_head = malloc(sizeof(t_ms));
	if (new_head == NULL)
		return (false);
	new_head->next = *head();
	new_head->ptr = ptr;
	*head() = new_head;
	return (true);
}

void	ft_m3_rm(void *ptr)
{
	t_ms	**curr;
	t_ms	*cache;

	if (ptr == NULL)
		return ;
	curr = head();
	while (*curr)
	{
		if ((*curr)->ptr == ptr)
		{
			cache = *curr;
			*curr = (*curr)->next;
			free(cache);
		}
		else
			curr = &(*curr)->next;
	}
}

void	ft_m3_each(void (*apply)(void *ptr))
{
	t_ms	*curr;

	curr = *head();
	while (curr)
	{
		apply(curr->ptr);
		curr = curr->next;
	}
}

void	ft_m3_cleanup(void)
{
	t_ms	*curr;
	t_ms	*cache;

	curr = *head();
	while (curr)
	{
		free(curr->ptr);
		cache = curr;
		curr = curr->next;
		free(cache);
	}
	*head() = NULL;
}
