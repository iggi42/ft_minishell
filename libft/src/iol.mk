# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    iol.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/05 22:55:50 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
ifndef SECT_iol

FT_LIB_PKGS += mem ll io str

SECT_iol += ft_iol_el_alloc.c ft_iol_elcmp.c ft_iol_el_free.c ft_iol_el_read.c
SECT_iol += ft_iol_pp_el.c

SECT_iol += ft_iol_append.c ft_iol_del.c ft_iol_free_always.c ft_iol_pp.c
# SECT_iol += ft_iol_read_till.c
SECT_iol += ft_iol_size.c ft_iol_str.c ft_iol_str_l.c ft_iol_write.c
endif
