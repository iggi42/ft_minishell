/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_iol.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IOL_H
# define LIBFT_IOL_H

# include "libft_ll.h"
# include <stdlib.h>

//! @name io list
//!@{

typedef t_list	*t_iol;

/**
 * @brief represent one part of an io list,
 * these are chained together to in a linked list.
 */
typedef struct s_iol_el
{
	char		*buffer;
	size_t		size;
	/** `free` is optional callback,
		that triggers when freeing the struct via ft_io_del(). */
	void		(*free)(struct s_iol_el *);
}				t_iol_el;

//! @brief pretty prints out an io list to stdout
void			ft_iol_pp(t_iol l);

//! @append a buffer pointer with a size to an iol */
void			ft_iol_append(t_iol *io_l, char *start, size_t size);

//! @brief write one io list to a fd
ssize_t			ft_iol_write(t_iol l, int fd);

//! @brief get the total size of all elements summed up
size_t			ft_iol_size(t_iol l);

//! @brief copy an the buffers of an io list into a single string.
char			*ft_iol_str(t_iol l);

size_t			ft_iol_str_l(t_iol l, char *target, size_t length);

//! @brief always free the buffer too, if ft_iol_del is called on the iol.
void			ft_iol_free_always(t_iol_el *el);

/**
 * @brief free an io list, calls ´iel->free´ to free the buffer to see if
 */
void			ft_iol_del(t_iol *l);

t_iol_el		*ft_iol_el_read(int fd, size_t s);

void			ft_iol_el_free(t_iol_el *el);

//! @brief pretty prints out one element of an io list to stdout
void			ft_iol_pp_el(t_iol_el *el);

//! @brief create news iol element
t_iol_el		*ft_iol_el_alloc(size_t size);

// return -1 on break not found
// else returns the index of the break found
typedef ssize_t	(*t_iol_breaker)(char *, size_t);

t_iol_el		*ft_iol_read_till(t_iol *iol_start, int fd, t_iol_breaker br);

//!@}
#endif
