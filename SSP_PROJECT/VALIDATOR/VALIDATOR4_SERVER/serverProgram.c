#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <dirent.h>
#include "server.h"
#include "utils.h"

#define FILENAME_LEN 27
#define HEADER_LEN (1+FILENAME_LEN+4)

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

typedef struct cardInfo
{
	char cardID[8];
	char busID[7];
	char ent;
	char entTime[14];
}CARDINFO;

typedef struct insp
{
	char inspID[8];
	char del1;
	char busID[7];
	char del2;
	CARDINFO stCardInfo;
	char del3;
	char code[2];
	char del4;
	char startTime[14];
}INSP;

typedef struct type
{
	char typeID[8];
	int totalCnt;
	int wrongCnt;
}TYPE;

TYPE stType[10];
INSP stInsp;
char fileList[20][100];
int nTypeCnt;
int nFileCnt;

void *receiveFile();
void readReportFile(char *currDate);
int compare_func_des(const void *a, const void *b);
int writeReportFile(char *currDate);
int scanDirectory(char *currDate);
void printReportFile(int sortFlag);

int main(void)
{
	pthread_t thread;
	int status =0;
	char buf[50]={0,};
	char currDate[10]={0,};
	int sortFlag =0;

	connectServer();

	pthread_create(&thread, NULL, receiveFile, NULL);
	pthread_join(thread, (void **)&status);

	while(1)
	{
		sortFlag =0;
		memset(currDate, 0x00, sizeof(currDate));
		gets(buf);

		if(memcmp(buf, "QUIT", 4)==0)
		{
			break;
		}
		else if(memcmp(buf, "REPORT", 6)==0)
		{
			GetCurrentDateString(currDate);
			scanDirectory(currDate);
			writeReportFile(currDate);
			printf("REPORT FINISH\n");
		}
		else
		{
			if(buf[9]=='C')
			{
				sortFlag =1;
			}
			memcpy(currDate, buf ,8);
			readReportFile(currDate);
			printReportFile(sortFlag);
		}
	}
}

void printReportFile(int sortFlag)
{
	int i=0;
	if(sortFlag)
	{
		qsort(stType, nTypeCnt, sizeof(TYPE), compare_func_des);
	}

	for(i=0; i<nTypeCnt; i++)
	{
		printf("%.8s %d %d\n", stType[i].typeID, stType[i].totalCnt, stType[i].wrongCnt);
	}
}

int compare_func_des(const void *a, const void *b)
{
	TYPE *left = (TYPE *)a;
	TYPE *right = (TYPE *)b;

	if(left->totalCnt < right->totalCnt)
	{
		return 1;
	}
	else if(left->totalCnt > right->totalCnt)
	{
		return -1;
	}
	return 0;
}

void readReportFile(char *currDate)
{
	FILE *fp;
	char pathBuf[100]={0,};
	char buf[100] ={0,};
	char *token;
	nTypeCnt =0;

	sprintf(pathBuf, "../SERVER/REPORT_%s.TXT", currDate);

	fp = fopen(pathBuf, "r");

	while(fgets(buf, 100, fp)!=NULL)
	{
		token = strtok(buf, " ");
		memcpy(stType[nTypeCnt].typeID, token, strlen(token));

		token = strtok(NULL, " ");
		stType[nTypeCnt].totalCnt = atoi(token);

		token = strtok(NULL, " ");
		stType[nTypeCnt].wrongCnt = atoi(token);
		nTypeCnt++;
	}

	if(fp)
	{
		fclose(fp);
	}
}

int scanDirectory(char *currDate)
{
	  DIR *dir;
	  struct dirent *ent;
	  char fileBuf[100] ={0,};
	  char fileDate[10]={0,};
	  char pathBuf[50]={0,};
	  char inspID[8]={0,};

	  dir = opendir("../SERVER");
	  if (dir != NULL) {

			  /* print all the files and directories within directory */
			  while ((ent = readdir (dir)) != NULL) {
				  //파일명에 .log 포함된 경우
				  	  if(strstr(ent->d_name,".TXT")!= NULL)
				  	  {
				  		  if(strstr(ent->d_name, "REPORT") != NULL)
				  		  {
				  			  continue;
				  		  }
				  		  printf ("%s\n", ent->d_name);
				  		  sprintf(pathBuf, "../SERVER/%s", ent->d_name);
				  		  memcpy(fileBuf,  ent->d_name, FILENAME_LEN);
				  		  memcpy(inspID, &fileBuf[0], 8);

				  		  makeTypeList(inspID);

				  		  memcpy(fileDate, &fileBuf[9], 8);

				  		  if(memcmp(currDate, fileDate, 8) != 0)
				  		  {
				  			  printf("날짜가 다름 \n");
				  			  continue;
				  		  }

				  		  memcpy(&fileList[nFileCnt], ent->d_name, FILENAME_LEN);
				  		  nFileCnt++;
				  	  }
			  }
			  closedir (dir);
	  } else {
			  /* could not open directory */
			  perror ("");
			  return EXIT_FAILURE;
	  }

}

void makeTypeList(char *inspID)
{
	int i=0;
	for(i=0; i<nTypeCnt; i++)
	{
		if(memcmp(inspID, stType[i].typeID, 8)==0)
		{
			break;
		}
	}

	if(i==nTypeCnt)
	{
		memcpy(stType[nTypeCnt].typeID, inspID, 8);
		nTypeCnt++;
	}
}

int writeReportFile(char *currDate)
{
	char inspID[8]={0,};
	char fileBuf[100]={0,};
	char buf[100]={0,};
	FILE *wfp;
	FILE *rfp;
	int i, j=0;
	char pathBuf[50]={0,};

	sprintf(fileBuf, "../SERVER/REPORT_%.8s.TXT", currDate);

	wfp = fopen(fileBuf, "w");

	for(i=0; i<nTypeCnt; i++)
	{
		for(j=0; j<nFileCnt; j++)
		{
			memcpy(inspID, &fileList[j][0], 8);
			if(memcmp(stType[i].typeID, inspID, 8)==0)
			{
				sprintf(pathBuf, "../SERVER/%s", fileList[j]);
				rfp = fopen(pathBuf, "r");
				while(fgets(buf, sizeof(buf), rfp) != NULL)
				{
					memcpy(&stInsp, buf, sizeof(INSP));

					if(memcmp(stInsp.code, "R1", 2)!=0)
					{
						stType[i].wrongCnt++;
					}

					stType[i].totalCnt++;
				}

				if(rfp)
				{
					fclose(rfp);
				}
			}
		}

		fprintf(wfp, "%.8s %d %d\n", stType[i].typeID, stType[i].totalCnt, stType[i].wrongCnt);
	}

	if(wfp)
	{
		fclose(wfp);
	}
}
void *receiveFile()
{
	char recvBuf[1024]={0,};
	char fileName[50]={0,};
	char path[50]={0,};
	FILE *fp;
	int nFileSize =0;
	char abFileSize[4]={0,};
	int fileCnt =0;
	int index =0;
	int recvLen =0;

	fileCnt =0;
	while(1)
	{
		index =0;
		recvLen = recv_message(recvBuf);
		//printf("recvBuf = %s\n", recvBuf);
		if(recvLen <=0)
		{
			printf("finish!\n");
			break;
		}

		if(recvBuf[0]=='*')
		{
			//printf("fileName ///////////////////\n");
			memcpy(fileName, &recvBuf[1], FILENAME_LEN);
			memcpy(abFileSize, &recvBuf[FILENAME_LEN+1], 4);
			nFileSize = atoi(abFileSize);

			sprintf(path, "../SERVER/%s", fileName);
			fp = fopen(path, "w");

			if(strlen(recvBuf)== HEADER_LEN)
			{
				continue;
			}
			else if(strlen(recvBuf)>HEADER_LEN)
			{
				index = HEADER_LEN;
			}

			fprintf(fp, "%s", &recvBuf[index]);
			fileCnt+= recvLen-index;
		}
		else
		{
			//printf("fileContents/////////////////\n");
			fprintf(fp, "%s", &recvBuf[index]);
			fileCnt += recvLen;
		}

		if(fileCnt >= nFileSize)
		{
			fileCnt = 0;
			if(fp)
			{
				fclose(fp);
			}
		}
	}
	printf("real Finish\n");
}
