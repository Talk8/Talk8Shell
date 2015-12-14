/* **************************
 * The ls command of shell
 * *************************/

/* *************************
 * support 2 kinds of ls command
 * 1.ls
 * 2.ls -a,
 * 3.othre params, add in later
 * **************************/

#include "main.h"

void sort_name(char name[PATH_SIZE][PATH_SIZE],int len)
{
	char str[PATH_SIZE];
	int i,j;
	int flag;

	memset(str,'\0',PATH_SIZE*sizeof(char) );
	flag = 1;

	for(i=0; i<len && flag; ++i)
	{
		flag = 0;
		for(j=len-1; j> i; --j)
		{
			if(0 < strcmp(name[j],name[j-1]))
			{
				strcpy(str,name[j]);
				strcpy(name[j],name[j-1]);
				strcpy(name[j-1],str);
				flag = 1;
			}
		}
	}
}

int print(char *str)
{
	char path[PATH_SIZE];
	char name[PATH_SIZE][PATH_SIZE];
	char *p;
	DIR * dir;
	struct dirent *dir_info;
	int i =0;

	memset(path,'\0',PATH_SIZE*sizeof(char) );
	memset(name,'\0',PATH_SIZE*sizeof(char) );

	if(NULL == (p=getcwd(path,PATH_SIZE)) )
	{
		printf("can't get the current directory \n");
		return 1;
	}

	if(NULL == (dir=opendir(path)) )
	{
		printf("can't open the directory %s \n",path);
		return 1;
	}


	while(NULL != (dir_info=readdir(dir)) )
		strcpy(name[i++],dir_info->d_name);

	closedir(dir);

	sort_name(name,i);

	// for ls command
	if( !strcmp(str,".") )
	{
		i -= 2; // can't show . and ..in result
		while(--i>=0)
			printf("%s \n",name[i]);
	}

	// for ls -a command
	if( !strcmp(str,"a") )
	{
		while(--i>=0)
			printf("%s \n",name[i]);

			//printf("%d :%s \n",i,name[i]);
	}

	return 0;
}

int lss(const char *p)
{
	char *start;
	char *end;
	int res;
	int i= 0;
	char *cmd[]=
	{
		"ls",
		"ls -a",
		//"ls -l",
		//"ls -al",
	};

	start = strstr(p,"ls");
	if(!start )
	{
		printf("can't support this format \n");
		return 1;
	}
	end = strchr(p,'\n');
	*end = '\0'; // make a normal string by \0

	for(i=0; i<sizeof(cmd)/sizeof(char*); ++i)
	{
		if( !strcmp(p,cmd[i]) )
		{
			switch(i)
			{
			case 0: res = print(".");
				break;
			case 1: res = print("a");
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				break;
			}
		}
	}

	if(res != 0)
		printf("can't support %s command ,please check again \n",p);

	return res;
}
