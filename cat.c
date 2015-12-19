/* **************************
 * The cat command of shell
 * *************************/

#include "main.h"

int cats(const char *p)
{
	char path[PATH_SIZE];
	char *start;
	char *end;
	char buf[PATH_SIZE];
	FILE *fp;

	memset(path,'\0',PATH_SIZE); // must init ,ohtrway there is a wrong result with @
	
	start = strchr(p,' ');
	end = strchr(p,'\n');
	if(!start || !end)
	{
		printf("can't support this format \n");
		return 1;
	}

	strncpy(path,p+4,end-start-1); // get the path in inputting command

	fp=fopen(path,"r"); // opne the file
	if(NULL==fp)
	{
		printf("can't opne file:%s \n",path);
		return 1;
	}

	while(NULL != fgets(buf,PATH_SIZE,fp)) // get the content of file ,and show them
		printf("%s",buf);

	fclose(fp); // close the file,after using it

	return 0;
}
