#include<stdio.h>

#define BUF_SIZE 64

typedef struct _input_type
{
	char * str; // the value of input
	int size;   // the length of value
}input_type;

input_type input[] =
{
	{"exit",4},
	{"cd",2},
	{"ls",2},
	{"date",4},
};

void cds(const char * p);
void lss(const char * p);
int dates(const char * p);
