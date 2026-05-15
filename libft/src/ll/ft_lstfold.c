/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_ll.h"
#include <stdlib.h>

void	*ft_lstfold(t_list *lst, void *acc, void *(*f)(void *, void *))
{
	if (lst == NULL)
		return (acc);
	acc = f(acc, lst->content);
	return (ft_lstfold(lst->next, acc, f));
}
