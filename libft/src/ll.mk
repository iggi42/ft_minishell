# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ll.mk                                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/05 22:55:50 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef SECT_ll

FT_LIB_PKGS += arr mem

SECT_ll = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstfold.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
	ft_lstsize.c ft_lststart.c
SECT_ll += ft_lst2arr.c
SECT_ll += ft_lst_pop.c ft_lst_push.c
SECT_ll += ft_lst_kv.c ft_lst_kv_keys.c  ft_lst_kv_init.c
endif
