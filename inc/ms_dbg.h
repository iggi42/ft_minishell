
#include "ms_cmd_t.h"
#include "ms_token.h"
#include "ms_parsing.h"
#include <libft_io.h>

void ms_print_cmd(char *prefix, t_ms_cmd *cmd);

void	ms_print_tokens(t_token *tkns);

void	print_redi(t_ms_redi *redi);

void print_parsing_result(char *desc, t_ms_parse_res *res);
