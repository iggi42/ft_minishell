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
# define ERR_MSG_UNCLOSED "syntax error: unexpected end of file"
// quote characters of a variable value wear these while they travel
// through the quote removal pass
# define MS_HIDDEN_SQ 1
# define MS_HIDDEN_DQ 2

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

int					ms_expand_var(t_token *prev, t_token **tkn);

char				*remove_quote(char *str);

char				*ms_quote_hide(char *value);
char				*ms_quote_show(char *str);

// true when the line holds nothing but spaces and tabs
int					ms_line_is_blank(char *input);

int					is_redirect(t_toke_type kind);
#endif
