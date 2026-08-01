/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fmt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FMT_H
# define LIBFT_FMT_H
# include <libft_iol.h>
# include <stdarg.h>

//! @brief format a string template into a io list for
t_iol	ft_fmt_parse(const char *tmpl);

//! @brief apply printf style operators to the parsed template
void	ft_fmt_apply(t_iol io_list, va_list *args);

#endif
