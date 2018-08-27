#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
static void ConvertDate(char *time,  int *nYear, int *nMonth, int *nDay, int *nHour, int *nMin, int *nSec );


int GetHashSHA256(const char * strInput, const char * strOutput )
{
	unsigned char outBuf[32] ={0,};
	int i =0;

//	mbedtls_sha256((unsigned char *)strInput, strlen(strInput), outBuf, 0);
	for(i=0; i<32; i++){
		sprintf(&strOutput[i*2], "%02X", outBuf[i]);
	}
	return 1;
}

static void ConvertDate(char *time,  int *nYear, int *nMonth, int *nDay, int *nHour, int *nMin, int *nSec )
{
	char year[5], month[3], day[3], hour[3], min[3], sec[3];

	strncpy(year, &time[0], 4); year[4] = 0;
	strncpy(month, &time[4], 2); month[2] = 0;
	strncpy(day, &time[6], 2); day[2] = 0;
	strncpy(hour, &time[8], 2); hour[2] = 0;
	strncpy(min, &time[10], 2); min[2] = 0;
	strncpy(sec, &time[12], 2); sec[2] = 0;

	*nYear = atoi(year);
	*nMonth = atoi(month);
	*nDay = atoi(day);
	*nHour = atoi(hour);
	*nMin = atoi(min);
	*nSec = atoi(sec);

}

int HourDiff(char *time1, char *time2)
{
	int year, month, day, hour, min, sec;
	struct tm user_stime1;
	struct tm user_stime2;
	time_t tm_st1, tm_st2;
	double d_diff;
	int nRet;

	ConvertDate(time1, &year, &month, &day, &hour, &min, &sec);
	user_stime1.tm_year = year- 1900;
	user_stime1.tm_mon = month- 1;
	user_stime1.tm_mday = day;
	user_stime1.tm_hour = hour;
	user_stime1.tm_min = min;
	user_stime1.tm_sec = sec;
	user_stime1.tm_isdst =0;

	ConvertDate(time2, &year, &month, &day, &hour, &min, &sec);
	user_stime2.tm_year = year- 1900;
	user_stime2.tm_mon = month- 1;
	user_stime2.tm_mday = day;
	user_stime2.tm_hour = hour;
	user_stime2.tm_min = min;
	user_stime2.tm_sec = sec;
	user_stime2.tm_isdst =0;

	tm_st1 = mktime(&user_stime1);
	tm_st2 = mktime(&user_stime2);

	d_diff = difftime(tm_st2, tm_st1);
	nRet = (int)d_diff/(60*60);

	return nRet;
}

void GetCurrentDateString(char *buf)
{
	time_t ct;
	struct tm stm;

	ct = time(NULL);
	stm = *localtime(&ct);
	sprintf(buf, "%04d%02d%02d", stm.tm_year+1900, stm.tm_mon+1, stm.tm_mday );
}

void GetCurrentDateTimeString(char *buf)
{
	time_t ct;
	struct tm stm;

	ct = time(NULL);
	stm = *localtime(&ct);
	sprintf(buf, "%04d%02d%02d%02d%02d%02d", stm.tm_year+1900, stm.tm_mon+1, stm.tm_mday ,  stm.tm_hour,  stm.tm_min,  stm.tm_sec);
}

int get_file_size(FILE *fp)
{
	int nRet;
	fseek(fp, 0, SEEK_END);
	nRet = ftell(fp);
	rewind(fp);

	return nRet;
}

int MoveFiles(char *oldname, char *newname)
{
	// delete exist file
	remove(newname);
	// move file
	return rename(oldname, newname);
}

