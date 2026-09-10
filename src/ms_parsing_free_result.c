
#include "ms_parsing.h"
#include <libft_arr.h>
#include <libft_mem.h>

void ms_free_parser_result(t_ms_parse_res *parsing_result)
{
	if(parsing_result == NULL)
		return;
	if(parsing_result->success)
		ft_arr_each((t_arr) parsing_result->source.cmds, (void (*)(t_arr_el)) ms_cmd_free);
	ft_free(parsing_result->source.error_msg);
	ft_free(parsing_result);
}
