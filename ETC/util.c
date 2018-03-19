#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static int get_int(char *value, int len);
time_t get_dtime(char *dtime);
int get_diff_dtime(char *asc_dtime1, char *asc_dtime2);
void TimeT2ASCDTime(time_t tSrcDTime, char *abDesASCDTime);

static int get_int(char *value, int len)
{
	char buf[256] ={0,};
	memcpy(buf, value, len);
	return atoi(buf);
}

time_t get_dtime(char *dtime)
{
	struct tm time;
	memset(&time, 0, sizeof(time));

	time.tm_year = get_int(&dtime[0], 4)-1900;
	time.tm_mon = get_int(&dtime[4], 2)-1;
	time.tm_mday = get_int(&dtime[6],2);
	time.tm_hour = get_int(&dtime[8],2);
	time.tm_min = get_int(&dtime[10],2);
	time.tm_sec = get_int(&dtime[12],2);

	return mktime(&time);
}

int get_diff_dtime(char *asc_dtime1, char *asc_dtime2)
{
	return get_dtime(asc_dtime2)-get_dtime(asc_dtime1);
}

void TimeT2ASCDTime(time_t tSrcDTime, char *abDesASCDTime)
{
	struct tm *time_ptr;
	char buf[15]={0};

	if(tSrcDTime ==0)
	{
		memset(abDesASCDTime, '0', 14);
		return;
	}
	time_ptr = localtime(&tSrcDTime);
	strftime(buf, 15, "%Y%m%d%H%M%S", time_ptr);
}
