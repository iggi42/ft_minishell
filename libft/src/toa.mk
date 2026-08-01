# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    toa.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/05 22:55:50 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef SECT_toa
FT_LIB_PKGS += mem str

SECT_toa += ft_btoa_b.c ft_btoa_bl.c ft_btoa.c
SECT_toa += ft_itoa_b.c ft_itoa_bl.c ft_itoa.c
SECT_toa += ft_ltoa_b.c ft_ltoa_bl.c ft_ltoa.c
SECT_toa += ft_ptoa_b.c ft_ptoa_bl.c ft_ptoa.c
SECT_toa += ft_ultoa_b.c ft_ultoa_bl.c ft_ultoa.c
endif
