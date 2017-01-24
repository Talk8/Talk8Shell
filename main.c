/* **************************
 * The main funtion of shell
 * *************************/

#include "main.h"


command_type cmd[] =
{
	{"exit",4},
	{"cd",2},
	{"ls",2},
	{"date",4},
	{"pwd",3},
	{"cat",3},
	{"less",4},
};

int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	int res = 1;
	int flag = 1;
	int index = 0;

	
	while(flag)
	{
		printf("|->");
		if(NULL == fgets(buf,BUF_SIZE,stdin))
			return 0;

		index = sizeof(cmd)/sizeof(command_type);
		while(index-- > 0)
		{
			res = strncmp(buf,cmd[index].str,cmd[index].size);
			if(res == 0)
			{
				switch(index)
				{
				case 0: // exec exit command
					flag = 0;
					break;
				case 1: // exec cd command
					cds(buf);
					break;
				case 2: // exec ls command
					lss(buf);
					break;
				case 3: // exec date command
					dates(buf);
					break;
				case 4: // exec pwd command
					pwds();
					break;
				case 5: // exec cat command
					cats(buf);
					break;
				case 6: // exec less command
					lesss(buf);
					break;
				default:
					printf("can't running this command \n");
					break;
				}

				index = -1; // if find the command, stop finding
			}
		}

		if(index == -1)
			printf("can't find command: %s",buf);
	}

	return 0;
}

