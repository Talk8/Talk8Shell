/* **************************
 * The date command of shell
 * *************************/

#include "main.h"

int dates(const char *p)
{
	struct tm *PtrTime;
	time_t Ttime;
	char buf[32];
	char *week[7]={"日 ","一 ","二 ","三 ","四 ","五 ","六 "};

	if(strlen(p)> 5)// \n is inside in command,so it is 5,only support date format
	{
		printf("can't support this format \n");
		return 1;
	}

	time(&Ttime); // get the time
	printf("%s",ctime(&Ttime)); // show the date,which is formated by string

	PtrTime = localtime(&Ttime); // get the localtime

	//show the date information
	printf("%04d年 %02d月 %02d日 星期%s",
					PtrTime->tm_year+1900,PtrTime->tm_mon+1,PtrTime->tm_mday,week[PtrTime->tm_wday]);

	//show the time information
	printf("%02d:%02d:%02d \n",PtrTime->tm_hour,PtrTime->tm_min,PtrTime->tm_sec);

	//show the date and time information
	strftime(buf,sizeof(buf)/sizeof(char),"%c %Z",PtrTime);
	printf("%s \n",buf);

	return 0;
}
