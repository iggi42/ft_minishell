/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_merle.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 04:24:26 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/07 04:24:33 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MERLE_H
# define LIBFT_MERLE_H
# include <stdbool.h>
# include <stddef.h>

// @brief add pointer to m3
bool	ft_m3_add(void *ptr);

// @brief mallocs a pointer and add this
void	*ft_m3_malloc(size_t n);

// @brief guess what this does
void	ft_m3_free(void *ptr);

// @brief remove a pointer from m3
void	ft_m3_rm(void *ptr);

// @brief call the apply function against each stored pointer
void	ft_m3_each(void (*apply)(void *ptr));

// @brief frees all the pointer malloced via ft_malloc
// and not freed yet via ft_free
void	ft_m3_cleanup(void);

#endif
