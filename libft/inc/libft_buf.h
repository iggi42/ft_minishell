/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_buf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BUF_H
# define LIBFT_BUF_H

# include <stdlib.h>
# include "libft_mem.h"

//! @name buffer list, basic get_next_line is written on this
//!@{

/** @brief wrapper of a buffer, together with its size; */
typedef struct s_buf
{
	size_t			size;
	t_byte			*p;
}					t_buf;

/** @brief create a new buffer with a given size
 * and allocate a buffer for it. */
t_buf				*ft_buf_new(size_t size);

/** @brief create a max BUFFER_SIZE buffer from a file descriptior fd. */
t_buf				*ft_buf_read(int fd);

/**
 * @brief to split buffer at a given pointer in it into 2 buffers.
 * the return value is the part to the left,
 * and the given pointer will be the last position of the it.
 * and the buffer 'b' will the one on the left of the index.
 */
t_buf				*ft_buf_split(t_buf **b, size_t left_len);

/** @brief concat to buffers together and frees the inputs */
t_buf				*ft_buf_cat(t_buf **left, t_buf **right);

/** @brief frees the memory of the given pointer
 * and sets the address of it to NULL */
void				ft_buf_free(t_buf **b);

/** @brief turn a buffer struct into a zero index c string */
char				*ft_buf_str(t_buf **b);

/** @brief copy a buffer from src to dest, basically cloning it */
void				ft_buf_cp(t_buf *src, t_buf *dest);

//!@}
#endif
