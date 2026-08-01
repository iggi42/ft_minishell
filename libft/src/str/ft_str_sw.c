/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_sw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 09:25:42 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/25 09:25:45 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"
#include <stdbool.h>
#include <stdint.h>

bool	ft_str_sw(const char *big, const char *little)
{
	return (ft_strncmp(big, little, ft_strlen(little)) == 0);
}
