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

SRCS += ms_redi.c ms_redi_apply.c
SRCS += ms_cmd_free.c ms_cmd_new.c ms_cmd_heredoc.c
SRCS += ms_dbg.c

SRCS += ms_env_core.c ms_env_crud.c ms_env_environ.c ms_env_special.c
SRCS += ms_exec_builtins.c ms_exec_builtins_cd.c ms_exec_builtins_echo.c ms_exec_builtins_env.c
SRCS += ms_exec_builtins_exit.c ms_exec_builtins_export.c ms_exec_builtins_pwd.c ms_exec_builtins_unset.c
SRCS += ms_exec.c ms_exec_cmd.c ms_exec_pipe.c ms_exec_child.c
SRCS += ms_signals.c ms_rl.c
SRCS += ms_exec_fs.c ms_exec_utils.c ms_is_path.c ms_pwd.c

SRCS += ms_expander.c ms_expander_utils.c
SRCS += ms_parsing_getlen.c
SRCS += ms_parsing.c ms_parsing_free_result.c ms_parsing_utils.c
SRCS += ms_repl.c ms_repl_prompt.c ms_repl_history.c
SRCS += ms_safe_fd.c bw_core.c
SRCS += ms_safe_mem.c
SRCS += ms_safe_os.c kg_core.c
SRCS += ms_token.c
SRCS += ms_token_utils.c
SRCS += ms_exit.c

SRC_DIR = src
BIN_DIR = bin
CPPFLAGS += -I./inc

TEST_DIR = test
# TESTS += parsing_test.c
TESTS += env_test.c token_test.c

## cflags here get also applied to libft binaries
FT_EXTRA_CFLAGS += -g

LDLIBS += -lreadline

-include libft/project.mk

# add the main here so it doesn't get added to tests
SRCS += ms_main.c
# SRCS += pipex_main.c

# TODO deduplicate OBJS here (with a sort?)
GIT_IGNORE += $(NAME)
$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $+

# pipex: $(NAME)
# 	cp $(NAME) pipex
