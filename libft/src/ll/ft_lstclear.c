/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 04:43:06 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_ll.h"
#include "libft_mem.h"

static void	ft_lstcut(t_list *lst, void (*del)(void *))
{
	t_list	*nxt;

	if (lst == NULL)
		return ;
	del(lst->content);
	nxt = lst->next;
	ft_free(lst);
	ft_lstcut(nxt, del);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	ft_lstcut(*lst, del);
	*lst = NULL;
}
