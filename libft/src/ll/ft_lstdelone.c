/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 04:33:11 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_ll.h"
#include "libft_mem.h"

void	ft_lstdelone(t_list **lst, void (*del)(void *))
{
	t_list	*frst;

	if (*lst == NULL)
		return ;
	frst = *lst;
	*lst = (*lst)->next;
	if (del)
		del(frst->content);
	ft_free(frst);
}
