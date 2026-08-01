# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    io.mk                                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/05 22:55:50 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef SECT_io

FT_LIB_PKGS += str toa
SECT_io += ft_putchar_fd.c ft_putendl_fd.c	ft_putnbr_fd.c ft_putstr_fd.c

FT_LIB_PKGS += fmt iol
SECT_io += ft_printf.c ft_printf_fd.c

SECT_io += ft_write.c

endif
