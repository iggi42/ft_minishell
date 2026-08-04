# ***************************************************************************  #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2026/08/04 22:02:10 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS += ms_repl.c ms_exec.c ms_parsing.c ms_env.c ms_exit.c

# steffi parser
SRCS += ms_token.c ms_token_utils.c ms_expander.c ms_expander_utils.c

SRC_DIR = src
BIN_DIR = bin
CPPFLAGS += -I./inc

TEST_DIR = test
# TESTS += parsing_test.c
TESTS += env_test.c token_test.c

## cflags here get also applied to libft binaries
FT_EXTRA_CFLAGS += -g

-include libft/project.mk
SRCS += ms_main.c

# TODO deduplicate OBJS here (with a sort?)
GIT_IGNORE += $(NAME)
$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $@ $+
