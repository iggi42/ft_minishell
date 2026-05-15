/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_char.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CHAR_H
# define LIBFT_CHAR_H

//! @name Character Classes
//!@{
/** @brief return 0 if c is not a alphanumerical character. */
int	ft_isalnum(int c);

/**  @brief return 0 if c is not a alphabetical character. */
int	ft_isalpha(int c);

/**  @brief return 0 if c is not an ascii character. */
int	ft_isascii(int c);

/**  @brief return 0 if c is not a digit character. */
int	ft_isdigit(int c);

/**  @brief return 0 if c is not a printable character. */
int	ft_isprint(int c);

/**  @brief return uppercase version of c, if c is a lowercase character. */
int	ft_toupper(int c);
int	ft_tolower(int c);
//!@}
#endif
