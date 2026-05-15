# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    arr.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/05 22:55:50 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef SECT_arr
FT_LIB_PKGS += mem

SECT_arr += ft_arr_len.c ft_arr_new.c ft_arr_each.c ft_arr_fold.c
SECT_arr += ft_arr_map.c ft_arr_nmap.c
endif
