/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_str.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STR_H
# define LIBFT_STR_H

# include <stddef.h>
# include <stdlib.h>

//! @name string
//!@{
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
size_t	ft_strlcat(char *dst, const char *src, size_t dst_size);

/** @brief allocates a memory for a string with length len. */
char	*ft_str_alloc(size_t len);
char	*ft_str_grow(char **input, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

//! @brief allocates a string from a template string and var args.
char	*ft_strf(const char *tmpl, ...);
char	*ft_strnxt(const char *s, int (*check)(int c));

// parses a long from an input string into a long
// returns 0 if parsing failed,
// otherwise returns the number of characters read from input
size_t	ft_str2l(const char *input, long *result);

// reads them as a fraction like seperated by /
size_t	ft_str2d(const char *input, double *result);

//!@}

#endif
