/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_cache.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:52:33 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/23 17:52:34 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_kv.h>
#include <libft_mem.h>
#include <stdbool.h>
#include <stddef.h>

static int	cmp_fd(void *a, void *b)
{
	return (*(int *)a - *(int *)b);
}

static t_kv	**data(void)
{
	static t_kv	*core;

	if (core == NULL)
		core = ft_kv_init(cmp_fd);
	return (&core);
}

// gets the pointer to BUFFERS_SIZE large cache of what could be left from
// earlier gnl calls
// can return NULL! (if key not found, for example)
char	*fdc_at(int fd, char *(*new)(void))
{
	char	*result;
	int		*new_key;

	result = ft_kv_get(*data(), &fd);
	if (result != NULL)
		return (result);
	result = new();
	new_key = (int *)ft_malloc(sizeof(int));
	ft_kv_put(*data(), new_key, result);
	return (result);
}

void		fdc_free(int fd)
{
	t_kv_pair *entry = ft_kv_pop(*data(), &fd);
	if(entry == NULL)
		return;
	ft_free(entry->key);
	ft_free(entry->val);
	ft_free(entry);
}

void		fdc_free_all(void);
