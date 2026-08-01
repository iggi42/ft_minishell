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

#define FDC_INIT 1
#define FDC_FREE 2

static t_kv	*fdc_core(int op)
{
	static t_kv	*store;

	if (op == FDC_FREE)
		store = (ft_kv_free(store, ft_kv_free_entry), NULL);
	if (op == FDC_INIT && store == NULL)
		store = ft_kv_init(cmp_fd);
	return (store);
}

void	*fdc_add(int fd, void *buffer)
{
	int		*new_key;
	t_kv	*store;

	new_key = (int *)ft_malloc(sizeof(int));
	store = fdc_core(FDC_INIT);
	if (!store || !new_key)
		return (ft_free(new_key), NULL);
	*new_key = fd;
	ft_kv_free_entry(ft_kv_put(store, new_key, buffer));
	return (buffer);
}

void	*fdc_pop(int fd, void *(constructor)(size_t size), size_t init_size)
{
	t_kv		*store;
	t_kv_pair	*entry;
	char		*result;

	store = fdc_core(FDC_INIT);
	if (!store)
		return (NULL);
	entry = ft_kv_pop(store, &fd);
	if (entry == NULL)
		return (constructor(init_size));
	result = entry->val;
	ft_free(entry->key);
	ft_free(entry);
	return (result);
}

void	fdc_cleanup(void)
{
	fdc_core(FDC_FREE);
}
