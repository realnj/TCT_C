#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "./server.h"

#define FILENAME_LEN 27
#define HEADER_LEN (1+FILENAME_LEN+4)

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

void *receiveFile();

int main(void)
{
	pthread_t thread;
	int status =0;
	connectServer();

	pthread_create(&thread, NULL, receiveFile, NULL);
	pthread_join(thread, (void **)&status);
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
		printf("recvBuf = %s\n", recvBuf);
		if(recvLen <=0)
		{
			break;
		}

		if(recvBuf[0]=='*')
		{
			memcpy(fileName, &recvBuf[1], FILENAME_LEN);
			memcpy(abFileSize, &recvBuf[FILENAME_LEN+1], 4);
			nFileSize = atoi(abFileSize);

			sprintf(path, "../SERVER/%s", fileName);
			printf("////path = %s\n", path);
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


}
