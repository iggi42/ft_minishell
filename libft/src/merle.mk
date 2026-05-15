# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    merle.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 04:19:52 by fkruger           #+#    #+#              #
#    Updated: 2026/04/11 00:35:58 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef SECT_merle
SECT_merle += ft_m3_core.c ft_m3_malloc.c ft_m3_free.c
#SECT_merle += ft_m3lloc.c

# use the m3 hooks instead of direct calls
$(BIN_DIR)/mem/ft_malloc.o: FT_EXTRA_CFLAGS += -DM3_ENABLED
$(BIN_DIR)/mem/ft_free.o: FT_EXTRA_CFLAGS += -DM3_ENABLED
endif
