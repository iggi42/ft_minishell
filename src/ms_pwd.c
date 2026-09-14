#include "ms_exit.h"
#include <limits.h>
#include <unistd.h>

char	*ms_pwd(void)
{
	static char	cwd[PATH_MAX];

	ms_exit_if(getcwd(cwd, PATH_MAX), "getpwd failed");
	return ((char *)&cwd);
}
