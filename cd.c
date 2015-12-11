/* **************************
 * The cd command of shell
 * *************************/

#include "main.h"

int cds(const char *p)
{
	char path[PATH_SIZE];
	char *start;
	char *end;
	int res;
	int n= 0;

	memset(path,'\0',PATH_SIZE); // must init ,ohtrway there is a wrong result with @
	
	start = strchr(p,' ');
	end = strchr(p,'\n');
	if(!start || !end)
	{
		printf("can't support this format \n");
		return 1;
	}

	strncpy(path,p+3,end-start-1); // get the path in inputting command

	res = chdir(path); //change dir

	if(res != 0)
		printf("%s is nod a path,please check again \n",path);

	return res;
}
