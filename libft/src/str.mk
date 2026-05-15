# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    str.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/05 22:55:50 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef SECT_str
FT_LIB_PKGS += char fmt iol mem

SECT_str += ft_atoi.c ft_split.c ft_str_alloc.c ft_strchr.c ft_strdup.c ft_strf.c
SECT_str += ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c
SECT_str += ft_strmapi.c
SECT_str += ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c
SECT_str += ft_strnxt.c ft_str2l.c ft_str2d.c
endif
