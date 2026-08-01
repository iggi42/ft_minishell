/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:34:31 by fkruger           #+#    #+#             */
/*   Updated: 2025/12/05 13:31:58 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fd_cache.h"
#include "get_next_line.h"
#include <libft_mem.h>

char	*ft_buf_str(t_buf **b)
{
	char	*result;
	size_t	i;

	if (*b == NULL || (*b)->size == 0)
	{
		ft_buf_free(b);
		return (NULL);
	}
	result = (char *)ft_malloc((*b)->size + 1);
	if (result == NULL)
	{
		ft_buf_free(b);
		return (NULL);
	}
	i = 0;
	while (i < (*b)->size)
	{
		*(result + i) = (char)*((*b)->p + i);
		i++;
	}
	*(result + i) = '\0';
	ft_buf_free(b);
	return (result);
}

char	*ft_buf_eol(t_buf *b)
{
	size_t	i;
	char	*current;

	i = 0;
	while (b != NULL && i < b->size)
	{
		current = (char *)(b->p + i++);
		if (*current == '\0' || *current == '\n')
			return (current);
	}
	return (NULL);
}

void	ft_buf_free(t_buf **b)
{
	if (*b == NULL)
		return ;
	if ((*b)->p)
		ft_free((*b)->p);
	ft_free(*b);
	*b = NULL;
}

char	*ft_gnl(int fd)
{
	t_buf	*line_buf;
	t_buf	*block;
	char	*line_eol;

	line_buf = fdc_pop(fd, (void *)(size_t)ft_buf_new, 0);
	if (line_buf == NULL)
		return (NULL);
	line_eol = ft_buf_eol(line_buf);
	while (line_eol == NULL)
	{
		block = ft_buf_read(fd);
		if (block == NULL)
			return (ft_buf_str(&line_buf));
		line_buf = ft_buf_cat(&line_buf, &block);
		if (line_buf == NULL)
			return (NULL);
		line_eol = ft_buf_eol(line_buf);
	}
	block = ft_buf_split(&line_buf, 1 + (t_byte *)line_eol - line_buf->p);
	if (block != NULL && block->size > 0)
		fdc_add(fd, block);
	else
		ft_free(block);
	return (ft_buf_str(&line_buf));
}
