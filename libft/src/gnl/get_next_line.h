/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:33:09 by fkruger           #+#    #+#             */
/*   Updated: 2025/12/03 16:39:22 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <libft_io_opts.h>
# include <libft_byte_t.h>

// wrapper of a buffer, together with its size;
typedef struct s_buf
{
	size_t				size;
	t_byte				*p;
}						t_buf;

// create a new buffer with a given size and allocate a buffer for it.
t_buf					*ft_buf_new(size_t size);

t_buf					*ft_buf_read(int fd);

// to split buffer at a given pointer in it into 2 buffers
// the return value is the part to the left,
// and the given pointer will be the last position of the it.
//     and the buffer 'b' will the one on the left of the index.
t_buf					*ft_buf_split(t_buf **b, size_t left_len);

// concat to buffers together and frees the inputs
t_buf					*ft_buf_cat(t_buf **left, t_buf **right);

// frees the memory of the given pointer and sets the address of it to NULL
void					ft_buf_free(t_buf **b);

// turn a buffer struct into a zero index c string
char					*ft_buf_str(t_buf **b);

// copy a buffer from to
void					ft_buf_cp(t_buf *from, t_buf *to);

// find the first occurence of any bytes in args (null terminated string)
t_byte					*ft_buf_chr(t_buf *b, t_byte *args);

#endif
