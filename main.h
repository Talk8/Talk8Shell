/* **************************
 * The head file of shell
 * *************************/


#ifndef SHELL_HEAD_FILE
#define SHELL_HEAD_FILE

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<sys/stat.h>
#include<sys/types.h>


#define BUF_SIZE 64
#define PATH_SIZE 256

typedef struct _command_type
{
	char * str; // the value of input
	int size;   // the length of value
}command_type;

int cds(const char * p);
int lss(const char * p);
int dates(const char * p);
int cats(const char * p);
int pwds();
int lesss(const char *p);

#endif
