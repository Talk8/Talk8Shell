/* **************************
 * The cp command of shell
 * *************************/

#include "main.h"

int cps(const char *p)
{
	int res = 0;
	size_t count = 0;
	size_t pcount = BUFSIZ;
	int fd_src,fd_des;
	char *start,*end;
	char src[PATH_SIZE],des[PATH_SIZE];
	char buf[BUFSIZ];
	FILE *p_src,*p_des;

	memset(src,'\0',PATH_SIZE); // must init ,ohtrway there is a wrong result with @
	memset(des,'\0',PATH_SIZE);
	memset(buf,'\0',BUFSIZ);

	p +=3; //conten of p is:"cp src des",move the point to location of 's'
	start = strchr(p,' ');
	end = strchr(p,'\n');
	if(!start || !end)
	{
		printf("can't support this format \n");
		return 1;
	}

	strncpy(src,p,start-p);       //get the source file name in inputting command
	p += start-p+1;               //move the pointer to location of 'd'
	strncpy(des,p,end-start-1);   //get the des file name inputting command, there is a \n, so -1

	//printf("src:%s \n",src);
	//printf("des:%s \n",des);

	//open source file
	p_src = fopen(src,"r");
	if(NULL == p_src)
	{
		printf("can't open file :%s \n",src);
		res = 1;
	}

	//open des file
	p_des = fopen(des,"w+");
	if(NULL == p_des)
	{
		printf("can't open file :%s \n",des);
		res = 1;
	}

	//read character from src and writ them to des
	while(0 < (count=fread(buf,sizeof(char),pcount,p_src)) )
	{
		if(ferror(p_src))
		{
			printf("reading file failed \n");
			res = 1;
			break;
		}

		fwrite(buf,sizeof(char),count,p_des);
		if(ferror(p_des))
		{
			printf("writing files failed \n");
			res = 1;
			break;
		}
	}

	//close source file
	if(-1 == fclose(p_src) )
	{
		printf("close file: %s failed \n",src);
		res = 1;
	}

	//close des file
	if(-1 == fclose(p_des) )
	{
		printf("close file: %s failed \n",des);
		res = 1;
	}

	return res;
}

/*
int cps(const char *p)
{
	int res = 0;
	size_t count = 0;
	int fd_src,fd_des;
	char *start,*end;
	char src[PATH_SIZE],des[PATH_SIZE];
	char buf[BUFSIZ];

	memset(src,'\0',PATH_SIZE); // must init ,ohtrway there is a wrong result with @
	memset(des,'\0',PATH_SIZE);
	memset(buf,'\0',BUFSIZ);

	p +=3; //conten of p is:"cp src des",move the point to location of 's'
	start = strchr(p,' ');
	end = strchr(p,'\n');
	if(!start || !end)
	{
		printf("can't support this format \n");
		return 1;
	}

	strncpy(src,p,start-p);       //get the source file name in inputting command
	p += start-p+1;               //move the pointer to location of 'd'
	strncpy(des,p,end-start-1);   //get the des file name inputting command, there is a \n, so -1

	//printf("src:%s \n",src);
	//printf("des:%s \n",des);

	//open source file
	fd_src = open(src,O_RDONLY);
	if(fd_src == -1)
	{
		printf("can't open file :%s \n",src);
		res = 1;
	}

	//open des file
	fd_des = open(des,O_WRONLY|O_CREAT,S_IRWXU|S_IRGRP|S_IROTH); //creat a file wiht 744 permision
	if(fd_des == -1)
	{
		printf("can't open file :%s \n",des);
		res = 1;
	}

	//read character from src and writ them to des
	while(0 != (count=read(fd_src,buf,BUFSIZ)) )
	{
		if(-1 == count)
		{
			printf("reading file failed \n");
			res = 1;
			break;
		}

		if(count != write(fd_des,buf,count) )
		{
			printf("writing files failed \n");
			res = 1;
			break;
		}
	}

	//close source file
	if(-1 == close(fd_src) )
	{
		printf("close file: %s failed \n",src);
		res = 1;
	}

	//close des file
	if(-1 == close(fd_des) )
	{
		printf("close file: %s failed \n",des);
		res = 1;
	}

	return res;
}
*/
