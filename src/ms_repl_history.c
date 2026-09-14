
#include <stdio.h> // TODO remove me for eval
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

void	ms_repl_history_add(char *line)
{
	if(line == NULL)
		return;
	if (isatty(STDIN_FILENO) == 0)
		return ;
	if (*line != '\0')
		add_history(line);
}

void ms_repl_history_clear(void)
{
	rl_clear_history();
}

