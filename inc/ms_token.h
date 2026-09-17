/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:08:28 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:08:41 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TOKEN_H
# define MS_TOKEN_H
# include <stddef.h>

typedef enum e_token_type
{
	T_PIPE,
	T_IN,
	T_OUT,
	T_OUT_APPEND,
	T_HERE_DOC,
	T_WORD,
}					t_toke_type;

typedef struct s_token
{
	t_toke_type		kind;
	char			*value;
	struct s_token	*next;
}					t_token;

// create a list of tokens from an string
t_token				*ms_tokenize(char *input);

// token list utils
void				append_token(t_token **list, char *value,
						enum e_token_type kind);
t_token				*free_token_list(t_token *list);

size_t				ms_parsing_count_cmds(t_token *tokens);

// char				*slice_and_dice(char *str, int start, int len, char *var);

void				del_empty_token(t_token **list);

// returns NULL if tokens have no syntax error
// otherwise returns a pointer to a error mesage string (never free it)
char				*ms_syntax_check(t_token *tokens);

void				ms_expand(t_token **list);

char				*remove_quote(char *str);

int					is_redirect(t_toke_type kind);
#endif
