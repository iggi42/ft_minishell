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

SRCS += ms_repl.c ms_exec.c ms_parsing.c
#ms_main.c
SRC_DIR = src
BIN_DIR = bin
CPPFLAGS += -I./inc

TEST_DIR = test
TESTS += parsing_test.c

## cflags here get also applied to libft binaries
FT_EXTRA_CFLAGS += -g

-include libft/project.mk

GIT_IGNORE += $(NAME)
$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $@ $+
