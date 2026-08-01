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

ifdef BIN_DIR
OBJS = $(SRCS:%.c=$(BIN_DIR)/%.o)
else
OBJS = $(SRCS:.c=.o)
endif

DEPS = $(OBJS:.o=.d)
DEV_FILES += .gitignore compile_flags.txt
GIT_IGNORE += $(OBJS) $(DEPS) $(DEV_FILES)

LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a
CPPFLAGS += -I$(LIBFT)/inc/
LDLIBS += $(LIBFT_A)

.PHONY: all
all: $(NAME)

SELF=$(firstword $(MAKEFILE_LIST))

# optional folders
ifdef SRC_DIR
VPATH += $(SRC_DIR)
GPATH += $(SRC_DIR)
endif

ifdef BIN_DIR
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
GIT_IGNORE += /$(BIN_DIR)
endif

ifdef TESTS
ifndef BIN_DIR
TESTS_O = $(TESTS:%.c=%.o)
else
TESTS_O = $(TESTS:%.c=$(BIN_DIR)/%.o)
$(BIN_DIR)/%.o: $(TEST_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
endif

.PHONY: test
test: tester
	./$<

ifdef TEST_DIR
VPATH += $(TEST_DIR)
endif

tester: $(TESTS_O) $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -lcriterion -o $@ $+

endif

# cleaning targets
all: $(NAME)
re: clean all
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) $@
	find -name '*.d' -print -delete

clean:
ifdef BIN_DIR
	$(RM) -r $(BIN_DIR)
else
	$(RM) $(OBJS) $(DEPS)
endif
	$(MAKE) -s -C $(LIBFT) $@

# dev utils targets
dev: $(DEV_FILES)
	$(MAKE) -s -C $(LIBFT) $@
dev_clean:
	$(RM) $(DEV_FILES)
	$(MAKE) -s -C $(LIBFT) $@

.PHONY: fclean clean re dev all

# development helper files
compile_flags.txt: $(SELF)
	@echo setup $@
	@echo -n > $@
	@for flag in $(CFLAGS) $(CPPFLAGS); do \
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
	$(MAKE) -s -C $(LIBFT) $(@F)

GIT_IGNORE += $(DEPS)
-include $(DEPS)
