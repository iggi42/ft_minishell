#!/usr/bin/env bash

make minishell

valgrind \
	--errors-for-leak-kinds=all \
	--leak-check=full \
	--show-error-list=yes \
	--show-leak-kinds=all \
	--suppressions=readline.supp \
	--trace-children=yes \
	--trace-children-skip="$(echo /bin/* /usr/bin/* /usr/sbin/* $(which norminette) | tr ' ' ',')" \
	--track-fds=all \
	--track-origins=yes \
	./minishell
