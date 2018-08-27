#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <netdb.h>
#include <pthread.h>
#include <errno.h>
//#include <glib.h>
#include "utils.h"
#include "client.h"

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
	char endTime[14];
}CARDINFO;

CARDINFO stCardInfo;

int checkLoginId(char *inputID, char*inputPwd );
int cardInspection(char *userID, char *busID, char *startTime);
int sendFile(char *ID);

int main(void)
{
	char busID[20]={0,};
	char inputID[20]={0,};
	char inputPwd[20]={0,};
	char startTime[20]={0,};

	while(1)
	{
		scanf("%s %s", inputID, inputPwd);
//		if(checkLoginID(inputID, inputPwd)==0)
//		{
//			printf("LOGIN SUCCESS\n");
			break;
//		}
//		else
//		{
//			printf("LOGIN FAIL\n");
//		}
	}

	while(1)
	{
		scanf("%s", busID);
		GetCurrentDateTimeString(startTime);
		if(strcmp(busID, "LOGOUT")==0)
		{
			break;
		}
		cardInspection(inputID, busID, startTime);
	}

	connectServer();
	sendFile(inputID);
}

int sendFile(char *ID)
{
	char pathBuf[50]={0,};
	char fileName[50]={0,};
	char szMoveFile[50]={0,};
	char szFoundFile[50]={0,};
	FILE *fp;
	DIR *dir;
	struct dirent *ent;
	char sendBuf[1024]={0,};
	int size =0;
	char abSize[5]={0,};

	sprintf(pathBuf, "../%s", ID);

	dir = opendir(pathBuf);
	  if (dir != NULL) {

			  /* print all the files and directories within directory */
			  while ((ent = readdir (dir)) != NULL) {
				  //파일명에 .log 포함된 경우
				  	  if(strstr(ent->d_name,".TXT")!= NULL)
				  	  {
				  		  printf ("%s\n", ent->d_name);
				  		  sprintf(fileName, "%s/%s", pathBuf, ent->d_name);
				  		  fp = fopen(fileName, "r");
				  		  size = get_file_size(fp);
				  		  sprintf(abSize, "%04d", size);

				  		  sprintf(sendBuf, "*%s%.4s", ent->d_name, abSize);
				  		  send_message(sendBuf);
				  		  printf("(1) sendBuf = %s\n", sendBuf);
				  		  memset(sendBuf, 0x00, sizeof(sendBuf));

				  		  while(fgets(sendBuf, 100, fp)!= NULL)
				  		  {
				  			  send_message(sendBuf);
				  			  printf("(2) sendBuf = %s\n", sendBuf);
				  			  memset(sendBuf, 0x00, sizeof(sendBuf));
				  		  }

				  		  if(fp)
				  		  {
				  			  fclose(fp);
				  		  }

				  		  sprintf(szMoveFile, "../BACKUP/%s", ent->d_name);
				  		  MoveFiles(fileName, szMoveFile);

				  	  }
			  }
			  closedir (dir);
	  } else {
			  /* could not open directory */
			  perror ("");
			  return EXIT_FAILURE;
	  }
	  return 0;
}

int cardInspection(char *userID, char *busID, char *startTime)
{
	FILE *fp;
	char fileName[50]={0,};
	char path[30]={0,};
	char cardBuf[50]={0,};
	char currTime[15]={0,};
	char code[3]={0,};

	sprintf(path, "../%s", userID);
	mkdir(path, 0777);

	sprintf(fileName, "%s/%s_%s.TXT", path, userID, startTime);

	fp = fopen(fileName, "w");

	while(1)
	{
		scanf("%s", cardBuf);
		GetCurrentDateTimeString(currTime);
		if(strcmp(cardBuf, "DONE")==0)
		{
			break;
		}

		memcpy(&stCardInfo, cardBuf, strlen(cardBuf));

		if(memcmp(stCardInfo.busID, busID, 7)!=0)
		{
			memcpy(code, "R2", 2);
		}
		else
		{
			if(stCardInfo.ent == 'F')
			{
				memcpy(code, "R3", 2);
			}
			else
			{
				if(HourDiff(currTime, stCardInfo.endTime)>3)
				{
					memcpy(code, "R4", 2);
				}
				else
				{
					memcpy(code, "R1", 2);
				}
			}
		}

		fprintf(fp, "%s#%s#%s#%.2s#%s\n", userID, busID, &stCardInfo, code, startTime);
	}

	if(fp)
	{
		fclose(fp);
	}
}

int checkLoginID(char *inputID, char *inputPwd)
{
	char chID[20]={0,};
	char chPwd[100]={0,};
	char outputPwd[100] ={0,};
	FILE *fp;
	int result =1;

	fp = fopen("../CLIENT/INSPECTOR.TXT", "r");

	while(fscanf(fp, "%s %s", chID, chPwd)>0)
	{
		if(strcmp(chID, inputID)==0)
		{
			GetHashSHA256(inputPwd, outputPwd);
			if(strcmp(outputPwd, chPwd)==0)
			{
				result =0;
				break;
			}
			else
			{
				break;
			}

		}

		memset(chID, 0x00, sizeof(chID));
		memset(chPwd, 0x00, sizeof(chPwd));
	}

	if(fp)
	{
		fclose(fp);
	}

	return result;
}
