# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mem.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/05 22:55:50 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef SECT_mem

SECT_mem += ft_free.c ft_malloc.c
SECT_mem += ft_bzero.c ft_calloc.c ft_iszero.c  ft_memchr.c
SECT_mem += ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_switch.c
endif
