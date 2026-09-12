
#include <stdbool.h>
#include <stdlib.h>

bool	ms_is_path(char *cmd)
{
	while (cmd != NULL)
	{
		if (*cmd == '/')
			return (true);
		if (*cmd == '\0')
			return (false);
		cmd++;
	}
	return (false);
}

