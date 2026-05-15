/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fmt_ops.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_FMT_OPS_H
# define LIBFT_FMT_OPS_H
# include "libft_iol.h"

void	ft_fmt_set_str(t_iol_el *el, char *s);
void	ft_fmt_set_c(t_iol_el *el, char c);
void	ft_fmt_set_ptr(t_iol_el *el, void *ptr);
void	ft_fmt_set_i(t_iol_el *el, int i);
void	ft_fmt_set_l(t_iol_el *el, long l);
void	ft_fmt_set_ui(t_iol_el *el, unsigned int i);
void	ft_fmt_set_hex(t_iol_el *el, unsigned int x);

#endif
