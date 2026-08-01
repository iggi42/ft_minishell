/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_eq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 09:19:50 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/25 09:19:52 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"
#include <stdbool.h>
#include <stdint.h>

bool	ft_str_eq(const char *a, const char *b)
{
	return (ft_strncmp(a, b, SIZE_MAX) == 0);
}
