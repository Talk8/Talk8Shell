/* **************************
 * The ls command of shell
 * *************************/

/* *************************
 * support 3 kinds of ls command
 * 1.ls
 * 2.ls -a,
 * 3.ls -l
 * 4.othre params, add in later
 * **************************/

#include "main.h"

void show_attr(char *name)
{
	struct stat buf;
	struct passwd *pwd;
	struct group *grp;
	char type ;
	char permission[9];
	int i = 0 ;

	memset(permission,'-',9*sizeof(char));

	if(!stat(name,&buf))
	{
		// get the type of file
		if(S_ISLNK(buf.st_mode))
			type = 'l';
		else if(S_ISREG(buf.st_mode))
			type = '-';
		else if(S_ISDIR(buf.st_mode))
			type = 'd';
		else if(S_ISCHR(buf.st_mode))
			type = 'c';
		else if(S_ISBLK(buf.st_mode))
			type = 'b';
		else if(S_ISFIFO(buf.st_mode))
			type = 'p';
		else if(S_ISSOCK(buf.st_mode))
			type = 's';

		// get the permission of file
		if(buf.st_mode & S_IRUSR)
			permission[0] = 'r';
		if(buf.st_mode & S_IWUSR)
			permission[1] = 'w';
		if(buf.st_mode & S_IXUSR)
			permission[2] = 'x';
		if(buf.st_mode & S_IRGRP)
			permission[3] = 'r';
		if(buf.st_mode & S_IWGRP)
			permission[4] = 'w';
		if(buf.st_mode & S_IXGRP)
			permission[5] = 'x';
		if(buf.st_mode & S_IROTH)
			permission[6] = 'r';
		if(buf.st_mode & S_IWOTH)
			permission[7] = 'w';
		if(buf.st_mode & S_IXOTH)
			permission[8] = 'x';

		// get the user name and group name
		pwd = getpwuid(buf.st_uid);
		grp = getgrgid(buf.st_gid);

		if(NULL == pwd)
		{
			printf("pw is null \n");
			exit(1);
		}
		if(NULL == grp)
		{
			printf("grp is null \n");
			exit(1);
		}
		// show file type
		printf("%c",type);

		// show permission of usr, grout and other
		while(i<9)
		{
			printf("%c",permission[i]);
			i++;
		}

		// show the count of link
		printf("%2d ",buf.st_nlink);

		// show the user name and group name
		printf("%-4s",pwd->pw_name);
		printf("%-4s",grp->gr_name);

		// show the size of file
		printf( "%6ld ",buf.st_size);

		// show the time of file
		printf("%.12s",ctime(&buf.st_mtime)+4); //+ 4 skip the weekday ,12s don't show year info

		// show the name of file
		printf(" %s\n",name);
	}
	else
	{
		printf("can't get the state of %s \n",name);
		exit(1);
	}
}
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

	// for ls -l command
	if( !strcmp(str,"l") )
	{
		i -= 2; // can't show . and ..in result
		while(--i>=0)
			show_attr(name[i]);
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
		"ls -l",
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
			case 2: res = print("l");
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
