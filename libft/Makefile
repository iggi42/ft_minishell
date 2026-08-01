# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2026/04/10 23:12:40 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# configuration variables
CC = cc
CFLAGS += -MD -Wall -Wextra -Werror -I./inc $(FT_EXTRA_CFLAGS)
# -MD to generate the .d files in $(DEPS)

NAME = libft
LIB = $(NAME).a
HEADER = $(addprefix ./inc/, \
	libft.h libft_buf.h libft_char.h libft_fmt.h libft_io.h libft_iol.h libft_ll.h \
	libft_locale.h libft_math.h libft_mem.h libft_str.h libft_toa.h libft_os.h)

SRC_DIR = src
BIN_DIR = bin

# ifndef FT_LIB_PKGS
# FT_LIB_PKGS += arr fmt io iol ll math mem os str toa merle
# endif
FT_LIB_PKGS += arr io mem str os merle gnl

# load SECT_$(pkg) for every pkgs
-include $(FT_LIB_PKGS:%=$(SRC_DIR)/%.mk) # 1
-include $(FT_LIB_PKGS:%=$(SRC_DIR)/%.mk) # 2
-include $(FT_LIB_PKGS:%=$(SRC_DIR)/%.mk) # 3
-include $(FT_LIB_PKGS:%=$(SRC_DIR)/%.mk) # 4
-include $(FT_LIB_PKGS:%=$(SRC_DIR)/%.mk) # 5
# allow our package dep tree to be 3 deep max for now
# a better solution than hard coding it that way, might be nice

FT_LIB_PKGS_OUTDIR=$(addprefix $(BIN_DIR)/, $(sort $(FT_LIB_PKGS)))

C_FILES = $(foreach p, $(sort $(FT_LIB_PKGS)), $(addprefix $(p)/, $(SECT_$(p))))

ifndef FT_APP_NAME
FT_APP_NAME := libft-dev
FT_EXTRA_CFLAGS += -DFT_APP_NAME=\"$(FT_APP_NAME)\"
endif

GIT_IGNORE += .depend
GIT_IGNORE += .gdb_history lldb_bugreport.txt
GIT_IGNORE += $(BIN_DIR)

SRCS = $(addprefix $(SRC_DIR)/, $(C_FILES))
OBJS = $(C_FILES:%.c=$(BIN_DIR)/%.o)
DEPS = $(OBJS:.o=.d)
DOC_FOLDER = doc
GIT_IGNORE += $(OBJS) $(DEPS)

SELF = $(firstword $(MAKEFILE_LIST))

# phony targets
all: $(NAME)
re: clean all
fclean: clean
clean:
	$(RM) $(OBJS) $(LIB) $(DEPS)
	$(RM) -r $(BIN_DIR)
$(NAME): $(LIB)
.PHONY: fclean clean re all

-include dev.mk

# core build rules
-include $(DEPS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

GIT_IGNORE += $(LIB)
libft.a: $(OBJS)
	$(AR) -src $@ $^
