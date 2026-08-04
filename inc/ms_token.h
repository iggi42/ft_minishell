#ifndef MS_TOKEN_H
# define MS_TOKEN_H
# include <stdbool.h>

typedef enum	e_token_type
{
	PIPE,
	IN,
	OUT,
	OUT_APPEND,
	HERE_DOC,
	WORD,
} t_toke_type;

typedef struct s_token
{
	t_toke_type kind;
	char	*value;
	struct	s_token	*next;
} t_token;

t_token	*ms_tokenize(char *input);
void	append_token(t_token **list, char *value, enum e_token_type kind);
t_token	*free_token_list(t_token *list);
char	*slice_and_dice(char *str, int start, int len, char *var);
void	del_empty_token(t_token **list);
char	*remove_quote(char *str);
#endif 
