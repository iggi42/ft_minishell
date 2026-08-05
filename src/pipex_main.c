/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:53:14 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/19 17:53:51 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ms_exec.h"
#include "ms_exec_utils.h"
#include "ms_redi.h"
#include "ms_utils.h"
#include <fcntl.h>
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_mem.h>
#include <libft_merle.h>
#include <libft_os.h>
#include <libft_str.h>
#include <libft_ll.h>
#include <stdlib.h>
#include <unistd.h>

void	print_help(void)
{
	ft_putendl_fd("computer sagt nein", 2);
}


enum e_ms_redi_kind	detect_redi(char *s)
{
	if (s == NULL)
		return (INVALID);
	if (!ft_strncmp(s, ">>", 2) && s[2] != '\0')
		return (OUT_APPEND);
	if (!ft_strncmp(s, "<<", 2) && s[2] != '\0')
		return (HERE_DOC);
	if (s[0] == '>' && s[1] != '\0')
		return (OUT);
	if (s[0] == '<' && s[1] != '\0')
		return (IN);
	return (INVALID);
}

t_ms_redi	*is_redi_op(char *s)
{
	enum e_ms_redi_kind	kind;
	t_ms_redi				*result;

	kind = detect_redi(s);
	if (kind == INVALID)
		return (NULL);
	result = ft_malloc(sizeof(t_ms_redi));
	result->kind = kind;
	if (kind == OUT || kind == IN)
		redi_set_path(result, ft_strdup(s + 1));
	else
		redi_set_path(result, ft_strdup(s + 2));
	return (result);
}

// very simply syntax for now
// ft_split and redirection operator get
size_t	parse_cmd(char *textform, t_ms_cmd *target)
{
	char	**split;
	t_list	*argv;
	t_list	*redis;
	size_t	i;
	t_ms_redi	*r_cache;

	split = ft_split(textform, ' ');
	i = ft_arr_len((t_arr)split);
	argv = NULL;
	redis = NULL;
	while (i--)
	{
		r_cache = is_redi_op(split[i]);
		if (r_cache)
		{
			ft_free(split[i]);
			ft_lst_push(&redis, r_cache);
		}
		else
			ft_lst_push(&argv, split[i]);
	}
	ft_free(split);
	target->argv = (char **)ft_lst2arr(argv);
	target->reds = (t_ms_redi **)ft_lst2arr(redis);
	return (ft_strlen(textform));
}

t_ms_cmd	*pipe_end(t_ms_cmd **pipe)
{
	size_t	i;

	if (*pipe == NULL)
		return (NULL);
	i = 0;
	while (pipe[i + 1])
		i++;
	return (pipe[i]);
}

static t_arr_el	my_parse(t_arr_el el)
{
	t_ms_cmd	*result;

	result = ms_malloc(sizeof(t_ms_cmd));
	ft_bzero(result, sizeof(t_ms_cmd));
	parse_cmd(el, result);
	return (result);
}

static void	set_redi(t_ms_cmd *cmd, t_ms_redi *redi)
{
	ft_arr_each((t_arr)cmd->reds, ft_free);
	ft_free(cmd->reds);
	cmd->reds = (t_ms_redi **)ft_arr_new(1);
	cmd->reds[0] = redi;
}

static void	build_normal_redis(t_ms_redi *redis, char *inpath, char *outpath)
{
	redis[0].kind = IN;
	redi_set_path(&redis[0], inpath);
	redis[1].kind = OUT;
	redi_set_path(&redis[1], outpath);
}

static void	build_bonus_redis(t_ms_redi *redis, char *hd_limiter, char *outpath)
{
	pid_t	writer_pid;

	redis[0].kind = HERE_DOC;
	redi_set_fd(&redis[0], fill_here_doc(hd_limiter, &writer_pid));
	// ft_wait(writer_pid);
	redis[1].kind = OUT_APPEND;
	redi_set_path(&redis[1], outpath);
}

int	main(int argc, char **argv)
{
	t_ms_redi	redis[2];
	int			result;
	t_ms_cmd	**shell_pipe;

	if (argc <= 4)
		return (print_help(), EXIT_FAILURE);
	if (!ft_strncmp("here_doc", argv[1], ft_strlen("heredoc") + 1))
	{
		if (argc <= 5)
			return (print_help(), EXIT_FAILURE);
		build_bonus_redis(&redis[0], argv[2], argv[argc - 1]);
		shell_pipe = (t_ms_cmd **)ft_arr_nmap((t_arr)(&argv[3]), argc - 4,
				my_parse);
	}
	else
	{
		build_normal_redis(&redis[0], argv[1], argv[argc - 1]);
		shell_pipe = (t_ms_cmd **)ft_arr_nmap((t_arr)(&argv[2]), argc - 3,
				my_parse);
	}
	set_redi(shell_pipe[0], &redis[0]);
	set_redi(pipe_end(shell_pipe), &redis[1]);
	result = ms_run_pipe(shell_pipe);
	ft_m3_cleanup();
	return (result);
}
