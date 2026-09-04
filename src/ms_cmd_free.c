#include "ms_cmd_t.h"
#include "ms_redi.h"
#include <libft_arr.h>
#include <libft_mem.h>

void	ms_cmd_free(t_ms_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))redi_free);
	ft_arr_each((t_arr)(cmd->argv), (void (*)(t_arr_el))ft_free);
	ft_free(cmd);
}
