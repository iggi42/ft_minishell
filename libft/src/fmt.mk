# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fmt.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/05 22:55:50 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef SECT_fmt

FT_LIB_PKGS += iol mem str toa

SECT_fmt += ft_fmt_apply.c ft_fmt_parse.c
SECT_fmt += ft_fmt_set_c.c ft_fmt_set_hex.c ft_fmt_set_i.c ft_fmt_set_l.c
SECT_fmt += ft_fmt_set_ptr.c ft_fmt_set_str.c ft_fmt_set_ui.c

endif
