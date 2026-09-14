TODO:

 - heredoc
 -- convert heredoc redis into in redis
 -- extend heredoc mechanism to wait for the writer pid only on clean up of a cmd
 -- have a resource manager to prevent zombie process in error cases zombie process in error cases (just copy bw to kg.c) (short for kindergarden)

TODO SIGNALS
TODO expand variables in heredoc
TODO word splitting?
TODO (maybe) check how bw and kg handle alloc failure during add
TODO write libft.d for libft.a to know when to rebuild it
TODO pop gnl cache on io wrappers (close, dup)
TODO check libft/Makefile and stop doing dangerous, experimental shit
TODO on the lst_functions where we can't ms_protect properly we need to react to errno going wrong
	=> build a safe wrapper around `ft_lst_push(&cache, new)`
     and similiar functions where you don't detected malloc failure via a returned NULL
     you will have to use errno instead
TODO funcheck and valgrind this bitch
TODO ft_arr_new shouldn't return a pointer to an array, maybe?
TODO cd - returns to OLDPWD

for on campus:
 - builtins: export without arguments ??
 - builtins: cd: does it correctly set PWD ?
 - check every 42 header for the email (write a sed script)

TODO implement comments # (wenn dir fad ist)
TODO (maybe): why does my gnl not like it when you heredoc into it?


TODO make a valgrind script for this 
VALGRIND_FLAGS=(
	--errors-for-leak-kinds=all
	--leak-check=full
	--show-error-list=yes
	--show-leak-kinds=all
	--suppressions="$UTILS/minishell.supp"
	--trace-children=yes
	--trace-children-skip="$(echo /bin/* /usr/bin/* /usr/sbin/* $(which norminette) | tr ' ' ',')"
	--track-fds=all
	--track-origins=yes
	--log-file="$TMP_OUTDIR/tmp_valgrind_out"
	)
