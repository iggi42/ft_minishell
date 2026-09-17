#include "ms_env.h"
#include "ms_exit.h"
#include <errno.h>
#include <limits.h>
#include <unistd.h>


// also gets called by cd, not just the pwd builtin
// so don't aggressively error out
char	*ms_pwd(void)
{
	static char	cwd[PATH_MAX];

	errno = 0;
	if(getcwd(cwd, PATH_MAX) == NULL)
	{
		ms_complain("getpwd failed", errno);
		ms_env_set_status(1);
		cwd[0] = '\0';
	}
	return ((char *)&cwd);
}
