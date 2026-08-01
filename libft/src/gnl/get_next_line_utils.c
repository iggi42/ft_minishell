/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:15:23 by fkruger           #+#    #+#             */
/*   Updated: 2025/12/03 15:57:43 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <libft_mem.h>
#include <unistd.h>

t_buf	*ft_buf_new(size_t size)
{
	t_buf	*result;

	result = (t_buf *)ft_malloc(sizeof(t_buf));
	if (result == NULL)
		return (NULL);
	result->size = size;
	result->p = (t_byte *)ft_malloc(size * sizeof(t_byte));
	if (result->p == NULL)
		return (ft_free(result), NULL);
	return (result);
}

t_buf	*ft_buf_read(int fd)
{
	t_byte	*p;
	int		read_result;
	t_buf	*result;

	p = (t_byte *)ft_malloc(BUFFER_SIZE);
	if (p == NULL)
		return (NULL);
	read_result = read(fd, p, BUFFER_SIZE);
	if (read_result <= 0)
		return (ft_free(p), NULL);
	result = (t_buf *)ft_malloc(sizeof(t_buf));
	if (result == NULL)
		return (free(p), NULL);
	result->size = read_result;
	result->p = p;
	return (result);
}

t_buf	*ft_buf_split(t_buf **b, size_t left_len)
{
	t_buf	*left;
	t_buf	*right;
	t_byte	*target;
	size_t	i;

	if (left_len >= (*b)->size)
		return (NULL);
	left = ft_buf_new(left_len);
	right = ft_buf_new((*b)->size - left_len);
	if (left == NULL || right == NULL)
		return (NULL);
	i = 0;
	while (i < (*b)->size)
	{
		if (i < left_len)
			target = left->p + i;
		else
			target = right->p + (i - left_len);
		*target = *((*b)->p + i++);
	}
	ft_buf_free(b);
	*b = left;
	return (right);
}

t_buf	*ft_buf_cat(t_buf **left, t_buf **right)
{
	size_t	i;
	t_buf	*result;
	t_byte	*src;

	i = 0;
	result = ft_buf_new((*left)->size + (*right)->size);
	if (result == NULL)
		return (NULL);
	while (i < result->size)
	{
		if (i < (*left)->size)
			src = (*left)->p + i;
		else
			src = (*right)->p + (i - (*left)->size);
		*(result->p + i++) = *src;
	}
	ft_buf_free(left);
	ft_buf_free(right);
	return (result);
}

// TODO make error codes or something else,
//	or something about necessary buffer size, see strlcpy useage
void	ft_buf_cp(t_buf *from, t_buf *to)
{
	size_t	i;

	if (from == NULL)
		to->size = 0;
	else
		to->size = from->size;
	i = 0;
	while (to != NULL && i < to->size)
	{
		*(to->p + i) = *(from->p + i);
		i++;
	}
}
