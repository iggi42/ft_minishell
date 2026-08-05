# ***************************************************************************  # #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2026/08/05 16:56:07 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# top level apis
SRCS += ms_repl.c ms_parsing.c ms_exec.c
## data structures
SRCS += ms_redi.c ms_cmd.c

# execution
SRCS += ms_exec_heredoc.c ms_exec_utils.c 

# parsing
SRCS += ms_expander.c ms_expander_utils.c  
SRCS += ms_token.c ms_token_utils.c

# utils

## environment variables handling
SRCS += ms_env.c

## resources trackers and clean
SRCS += ms_utils_exit.c
SRCS += ms_utils_malloc.c bw_core.c


SRC_DIR = src
BIN_DIR = bin
CPPFLAGS += -I./inc

TEST_DIR = test
# TESTS += parsing_test.c
TESTS += env_test.c token_test.c

## cflags here get also applied to libft binaries
FT_EXTRA_CFLAGS += -g

-include libft/project.mk

# add the main here so it doesn't get added to tests
SRCS += ms_main.c

# TODO deduplicate OBJS here (with a sort?)
GIT_IGNORE += $(NAME)
$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $@ $+
