/* **************************
 * The pwd command of shell
 * *************************/

#include "main.h"

int pwds()
{
	char buf[PATH_SIZE];
	char *res;

	res = getcwd(buf,PATH_SIZE);

	if(res)
	{
		printf("%s\n",buf);
		return 0;
	}
	else
		return 1;
}
