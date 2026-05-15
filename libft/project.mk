# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    project.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:10:11 by fkruger           #+#    #+#              #
#    Updated: 2025/12/11 12:20:33 by fkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# this is to be included in standard projects that use libft
# or copied as boiler plate if includes are not allowed ^^

# configuration variables
CC = cc
CFLAGS += -MD -Wall -Wextra -Werror $(FT_EXTRA_CFLAGS)

ifndef FT_APP_NAME
export FT_APP_NAME := $(NAME)
export FT_EXTRA_CFLAGS += -DFT_APP_NAME=\"$(FT_APP_NAME)\"
endif

GIT_IGNORE += .depend
GIT_IGNORE += .gdb_history
GIT_IGNORE += $(NAME)

ifdef C_FILES

ifdef SRC_DIR
SRCS += $(addprefix $(SRC_DIR)/, $(C_FILES))
else
SRCS += $(C_FILES)
endif

ifdef BIN_DIR
OBJS = $(C_FILES:%.c=$(BIN_DIR)/%.o)
else
OBJS = $(SRCS:.c=.o)
endif

endif # of ifdef C_FILES

DEPS = $(OBJS:.o=.d)
DEV_FILES += .gitignore compile_flags.txt
GIT_IGNORE += $(OBJS) $(DEPS) $(DEV_FILES)

LIBFT = ./libft
LIBFT_A = ./libft/libft.a
CFLAGS += -I./libft/inc/
LDLIBS += $(LIBFT_A)

SELF=$(firstword $(MAKEFILE_LIST))

# phony targets
all: $(NAME)
re: clean all
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) $@
	find -name '*.d' -print -delete
clean:
	$(RM) $(OBJS) $(DEPS)
	$(MAKE) -C $(LIBFT) $@
dev: $(DEV_FILES)
	$(MAKE) -C $(LIBFT) $@
dev_clean:
	$(RM) $(DEV_FILES)
	$(MAKE) -C $(LIBFT) $@
debug: FT_EXTRA_CFLAGS += -g
debug: clean $(NAME)
.PHONY: fclean clean re all dev debug

# development helper files
compile_flags.txt: $(SELF)
	@echo setup $@
	@echo -n > $@
	@for flag in $(CFLAGS); do \
		echo $$flag >> $@ ; \
	done

.gitignore: $(SELF)
	@echo setup $@
	@for ig in $(GIT_IGNORE); do \
		echo $$ig >> $@ ; \
	done

GIT_IGNORE += /libft/*.o /libft/*.d
# core build rules
$(LIBFT_A): $(LIBFT)
	$(MAKE) -C $(LIBFT)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

GIT_IGNORE += $(DEPS)
-include $(DEPS)
