# ***************************************************************************  #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/11 12:20:33 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

C_FILES += main.c
SRC_DIR = src
BIN_DIR = bin

# FT_EXTRA_CFLAGS += -g
all: $(NAME)

libft/project.mk:
	git clone git@github.com:iggi42/ft_libft.git libft

-include libft/project.mk

GIT_IGNORE += $(NAME)
$(NAME): $(OBJS) $(LIBFT_A) 
	$(CC) $(CFLAGS) -o $@ $^
