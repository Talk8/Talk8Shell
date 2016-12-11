/* **************************
 * The less command of shell
 * *************************/

#include "main.h"

int get_term_info(int *row, int *col);

int lesss(const char *p)
{
	char cmd;
	char file_name[PATH_SIZE];
	char *start;
	char *end;
	char buf[PATH_SIZE];
	FILE *fp;
	int current_line = 0; //the line count of showing in terminal
	int term_row = 0;     //the row count of current terminal
	int term_col = 0;     //the column count of current terminal
	int back_count = 0;   //the count of j cmd, in order to back the line for k cmd
	int res = 0;
	fpos_t begin_pos,pos;

	memset(file_name,'\0',PATH_SIZE); // must init ,ohtrway there is a wrong result with @

	printf("cmd is %s \n",p);
	if(strlen(p) == 5)// the command should be "less file_name ",and the length of  "less\n"is 5
	{
		printf("Missing filename (\"less --help\" for help) \n");
		return 1;
	}

	start = strchr(p,' ');
	end = strchr(p,'\n');
	if(!start || !end)
	{
		printf("can't support this format \n");
		return 1;
	}

	strncpy(file_name,p+5,end-start-1); // get the file name in inputting command

	fp=fopen(file_name,"r"); // opne the file
	if(NULL==fp)
	{
		printf("can't opne file:%s \n",file_name);
		return 1;
	}

	//get the location of file,in order to run k cmd
	res = fgetpos(fp,&begin_pos);
	if(res != 0)
	{
		printf("get the location of file failed \n");
		return 1;
	}

	//get the current line and cols
	res = get_term_info(&term_row,&term_col);
	if(res == 1)
	{
		printf("get the termial info failed \n");
		return 1;
	}

	//show the content of file, and showing line is equal 'term_row'
	while(NULL != fgets(buf,PATH_SIZE,fp))
	{
		//just for show the content in 1 terminal
		if(current_line < term_row-1)
		{
			printf("line: %-4d:",current_line);
			printf("%s",buf);
			current_line++;
		}
		else //wait the new commend of terminal
		{
			//close the echo and buffer
			system("stty -echo -icanon");

			cmd = getchar(); // get the commend

			//open the echo and buffer
			system("stty echo icanon");

			if(cmd == 'q')
			{
				current_line = 0;
				printf("Exit less cmd. \n");

				break;
			}
			else if(cmd == 'j')
			{
				printf("line: %-4d:",current_line);
				printf("%s",buf);

				back_count += 1; // add the count of j cmd
				current_line += 1;
			}
			else if(cmd == 'k')
			{
				back_count -= 1; // reduce the count of k cmd
				current_line = 0;

				//go back to the beaging of file,and then go to the new location for k cmd
				fsetpos(fp,&begin_pos);
				while(current_line++ < back_count)
				{
					fgets(buf,PATH_SIZE,fp);
				}
				//get the right location of k cmd, and then set this location
				fgetpos(fp,&pos);
				fsetpos(fp,&pos);

				current_line = 0; // it is used as temp, must keek to 0
			}
			else
			{
				printf("can't running this cmd in less \n");
			}
		}
	}

	fclose(fp); // close the file,after using it

	return 0;
}

//main function is used for getting count of line and cols in curretn terminal
int get_term_info(int *row, int *col)
{
	int res =0;

	res = setupterm(NULL,fileno(stdout),NULL);
	if(res == -1)
	{
		printf("set terminal failed \n");
		return 1;
	}

	*row = tigetnum("lines");
	*col = tigetnum("cols");

	if(-2 != *row)
		printf("Terminal row:%d \n",*row);
	else
		printf("get count of row failed \n");

	if(-2 != *col)
		printf("Terminal colum:%d \n",*col);
	else
		printf("get count of colum failed \n");

	if(-2 == *row || -2 == *col)
		return 1;

}
