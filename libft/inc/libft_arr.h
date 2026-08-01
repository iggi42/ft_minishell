/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_arr.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ARR_H
# define LIBFT_ARR_H
# include "libft_arr_t.h"
# include <stdbool.h>
# include <stddef.h>

t_arr		*ft_arr_new(size_t size);
size_t		ft_arr_len(t_arr arr);

// call 'apply' against each element of the array
void		ft_arr_each(t_arr arr, void (*each)(t_arr_el el));

// call 'apply' against the first n elements of the array
//   (ignores NULL terminators and feed them into apply instead).
void		ft_arr_neach(t_arr arr, size_t n, void (*each)(t_arr_el el));

t_arr		*ft_arr_map(t_arr input, t_arr_el (*map)(t_arr_el el));
t_arr		*ft_arr_nmap(t_arr input, size_t n, t_arr_el (*map)(t_arr_el el));

// fold bf(from lower to higher index) over the given array
// void* fold(void *acc, void *arr_el)
void		*ft_arr_fold(t_arr arr, void *(*fold)(void *, t_arr_el), void *acc);

// TODO implementation
void		*ft_arr_nfold(t_arr arr, void *(*fold)(void *, t_arr_el),
				void *acc);

t_arr_el	*ft_arr_find(t_arr arr, bool (*valid)(t_arr_el));

#endif
