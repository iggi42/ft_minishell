/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_toa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TOA_H
# define LIBFT_TOA_H

# include <stdlib.h>
# include "libft_byte_t.h"

//! @name itoa and friends
//!@{
/**
 * @brief convert an int to a decimal ascii string
 */
char	*ft_itoa(int i);
char	*ft_itoa_b(int i, const char *alphabet);
size_t	ft_itoa_bl(int i, char *target, size_t length, const char *alphabet);

char	*ft_btoa(t_byte byte);
char	*ft_btoa_b(t_byte byte, const char *alphabet);
size_t	ft_btoa_bl(t_byte byte, char *target, size_t length, const char *alph);

/**
 * @brief convert a ptr to a hex ascii string
 */
char	*ft_ptoa(void *ptr);
char	*ft_ptoa_b(void *ptr, const char *alphabet);
size_t	ft_ptoa_bl(void *ptr, char *target, size_t max_len, const char *alph);

/**
 * @brief convert a long to a decimal ascii string
 */
char	*ft_ltoa(long n);

/**
 * @brief convert a long with the given alphabet.
 */
char	*ft_ltoa_b(long n, const char *alphabet);

/**
 * @brief convert a long with the given alphabet, if length is sufficent
 */
size_t	ft_ltoa_bl(long nb, char *target, size_t length, const char *alphabet);

/**
 * @brief unsigned convert a long to a decimal ascii string
 */
char	*ft_ultoa(unsigned long n);

/**
 * @brief unsigned convert a long with the given alphabet.
 */
char	*ft_ultoa_b(unsigned long n, const char *alphabet);

/**
 * @brief write n to target in using the digits from alphabet.
 * returns the necessary string length, only wrote if space >= space
 *
 * we use this really as central work horse for the the other integer
 * to ascii functions.
 *
 * so keep the interface steady and optimise performance maybe
 */
size_t	ft_ultoa_bl(unsigned long nb, char *target, size_t length,
			const char *alphabet);

//!@}
#endif
