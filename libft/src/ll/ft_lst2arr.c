/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:03:45 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/19 15:03:49 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_arr.h"
#include "libft_ll.h"

t_arr	*ft_lst2arr(t_list *head)
{
	size_t	s;
	size_t	i;
	t_arr	*result;

	i = 0;
	s = ft_lstsize(head);
	result = ft_arr_new(s);
	while (result != NULL && i < s)
	{
		result[i++] = head->content;
		head = head->next;
	}
	return (result);
}
