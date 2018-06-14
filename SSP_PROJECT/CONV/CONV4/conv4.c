#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <netdb.h>
#include <pthread.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
typedef struct log
{
	char abTime[19];
	char del1;
	char abLogType[2];
	char del2;
	char abMsg[9];
	char tmp[2];
}LOG;

typedef struct type
{
	char abTypeName[2];
	int nTypeCnt;
}TYPE;

LOG *stLog;
TYPE stType[20];
int nTotalCnt;
int nTypeCnt;

int readFile(char *path);
int makeTypeList(char *type);
int writeFile(char *path);
void *writeEachLogFile(void *data);

int main(int argc, char *argv[])
{
	char *readPath = "./LOGFILE_B.TXT";
	char *writePath = "./REPORT_4.TXT";

	pthread_t p_thread[100];
	int thr_id;
	int status;
	int index = 0;

	readFile(readPath);
	writeFile(writePath);
//	writeEachLogFile();

	printf("nTotalCnt =%d\n", nTotalCnt );

	for(index=0; index<nTotalCnt; index++)
	{
		thr_id = pthread_create(&p_thread[index], NULL, writeEachLogFile, (void *)&index);

		if(thr_id<0)
		{
			printf("thread create error\n");
		}

		pthread_join(p_thread[index], (void **)&status);
	}
	return 0;
}

int makeTypeList(char *type)
{
	int i =0;
	for(i=0; i<nTypeCnt; i++)
	{
		if(memcmp(type, stType[i].abTypeName, 2)==0)
		{
			stType[i].nTypeCnt++;
			break;
		}
	}

	if(i==nTypeCnt)
	{
		memcpy(stType[nTypeCnt].abTypeName, type, 2);
		stType[nTypeCnt].nTypeCnt = 1;
		nTypeCnt++;
	}

	return 0;
}

int readFile(char *path)
{
	FILE *rfp;
	char readBuf[100] ={0,};
	rfp = fopen(path, "r");

	while(fgets(readBuf, 100, rfp) != NULL)
	{
		stLog = (LOG*)realloc(stLog, sizeof(LOG)*(nTotalCnt+1));
		memcpy(&stLog[nTotalCnt], readBuf, strlen(readBuf));

		makeTypeList(stLog[nTotalCnt].abLogType);
		nTotalCnt++;
	}

	if(rfp)
	{
		fclose(rfp);
	}

	return 0;
}

int writeFile(char *path)
{
	FILE *wfp;
	int i =0;

	wfp = fopen(path, "w");

	for(i=0; i<nTypeCnt; i++)
	{
		fprintf(wfp, "%.2s#%d\n", stType[i].abTypeName, stType[i].nTypeCnt);
	}

	if(wfp)
	{
		fclose(wfp);
	}
	return 0;
}

void *writeEachLogFile(void *data)
{
	int i, j=0;
	char fileName[20] ={0,};
	char convBuf[100] ={0,};
	FILE *fp;
	FILE *fconv;
	char msg[20] ={0,};

	i = *((int*)data);

	sprintf(fileName, "TYPELOG_4_%.2s.txt", stLog[i].abLogType);
	fp = fopen(fileName, "a+");

	sprintf(convBuf, "./CODECONV.EXE %.9s", stLog[i].abMsg);
	fconv = popen(convBuf, "r");

	if(fconv == NULL)
	{
		printf("popen fail\n");
		break;
	}

	while(fgets(msg, 20, fconv) != NULL)
	{

	}

	fprintf(fp, "%.19s#%.2s#%.9s\n", stLog[i].abTime, stLog[i].abLogType, msg);

	if(fp)
	{
		fclose(fp);
	}
	return 0;
}
