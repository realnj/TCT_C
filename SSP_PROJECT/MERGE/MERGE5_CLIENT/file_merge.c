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
#include "./client.h"

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

typedef struct list
{
	char fileName[20];
	int fileVers;
	char useYN;
}LIST;

LIST stSourceList[100];
LIST stTargetList[100];

int sCnt;
int tCnt;

int updateTargetFile();
int readDirectory(char *inputPath);
int readSourceFile(char *path);
int readTargetFile(char *path);
int writeResultFile();
void *inputMenuLoop();
int main()
{
	char *sourcePath = "./source";
	char *targetPath = "./target";

	pthread_t thread;
	int status=0;

	//readDirectory(sourcePath);
	readDirectory(targetPath);

	//readSourceFile(sourcePath);
	readTargetFile(targetPath);

	pthread_create(&thread, NULL, inputMenuLoop, NULL);
	connectServer("client");

	pthread_join(thread, (void**)&status );
	//writeResultFile();
//	updateTargetFile();

	return 0;
}
void *inputMenuLoop()
{
	char buf[1024]={0,};
	char buf2[1024]={0,};
	char lineBuf[50][50]={0,};
	int recvLen =0;
	char *token1;
	char *token;
	int nFileSize=0;
	int i=0;
	int index =0;

	while(1)
	{
		printf("SEND MESSAGE TO SERVER\n");
		scanf("%s", buf);

		if(strcmp(buf, "quit")==0)
		{
			printf("quit program\n");
			memset(buf, 0x00, 100);
			exit(1);
			break;
		}
		else if(strcmp(buf, "list")==0)
		{
			send_message(buf);
		}
		memset(buf, 0x00, sizeof(buf));

		while(1)
		{
			memset(buf2, 0x00, sizeof(buf2));
			recvLen = recv_message(buf2);

			if(buf2[0] >= '0' && buf2[0] <= '9')
			{
				nFileSize = atoi(buf2);

				if(strlen(buf2)==5)
				{
					index=0;
					continue;
				}
				else
				{
					index =5;
				}
			}

			token = strtok(&buf2[index], "\r\n");

			while(token != NULL)
			{
				memcpy(lineBuf[sCnt], token, strlen(token));
				sCnt++;
				token = strtok(NULL, "\r\n");
			}
			memset(buf2, 0x00, sizeof(buf2));

			for(i=0; i<sCnt; i++)
			{
				token1 = strtok(lineBuf[i], "_");
				memcpy(&stSourceList[i].fileName, token, strlen(token));
				token1 = strtok(NULL, "_");
				stSourceList[i].fileVers = atoi(token1);
			}

			writeResultFile();

			if(recvLen <= nFileSize)
			{
				break;
			}
		}

		//printf("finish==========\n");
	}
}
int updateTargetFile()
{
	FILE *resultfp;
	char buf[20] ={0,};
	char fileBuf[100] ={0,};
	char *fileName;
	char *code;

	resultfp = fopen("result.txt", "r");

	while(fgets(buf, 20, resultfp)!= NULL)
	{
		printf("buf =[%s]\n", buf);
		fileName = strtok(buf, "_");
		code = strtok(NULL, "_");

		if(code[0]=='C')
		{
			//printf("create !!!!!!!!!!!!\n");
			sprintf(fileBuf, "cp ./source/%s ./target/%s", fileName,fileName);
			system(fileBuf);
		}

		if(code[0] == 'D')
		{
			//printf("delete !!!!!!!!!!!!\n");
			sprintf(fileBuf, "rm ./target/%s",fileName);
			system(fileBuf);
		}

		if(code[0] == 'U')
		{
			//printf("update !!!!!!!!!!!!\n");
		}
	}
	if(resultfp)
	{
		fclose(resultfp);
	}
	return 0;
}

int readSourceFile(char *path)
{
	FILE *sfp;
	char buf[50]={0,};
	char *token;
	char pathBuf[50]={0,};
	sprintf(pathBuf, "%s/file_list.txt", path);

	sfp = fopen(pathBuf, "r");

	while(fgets(buf, 100, sfp) != NULL)
	{
		token = strtok(buf, "_");
		strcpy(stSourceList[sCnt].fileName, token);

		token = strtok(NULL, "_");
		stSourceList[sCnt].fileVers = atoi(token);
		sCnt++;
	}

	if(sfp)
	{
		fclose(sfp);
	}

	return 0;
}

int readTargetFile(char *path)
{
	FILE *sfp;
	char buf[50]={0,};
	char *token;
	char pathBuf[50]={0,};
	sprintf(pathBuf, "%s/file_list.txt", path);

	sfp = fopen(pathBuf, "r");

	while(fgets(buf, 100, sfp) != NULL)
	{
		token = strtok(buf, "_");
		strcpy(stTargetList[tCnt].fileName, token);

		token = strtok(NULL, "_");
		stTargetList[tCnt].fileVers = atoi(token);
		tCnt++;
	}


	if(sfp)
	{
		fclose(sfp);
	}

	return 0;
}

int writeResultFile()
{
	FILE *resultfp;
	int i, j=0;

	resultfp = fopen("result.txt", "w");

	for(i=0; i<sCnt; i++)
	{
		for(j=0; j<tCnt; j++)
		{
			if(strcmp(stSourceList[i].fileName, stTargetList[j].fileName)==0)
			{
				if(stSourceList[i].fileVers > stTargetList[j].fileVers)
				{
					fprintf(resultfp, "%s_C\n",  stSourceList[i].fileName);
					stTargetList[j].useYN = 1;
					break;
				}
				else
				{
					fprintf(resultfp, "%s_U\n",  stSourceList[i].fileName);
					stTargetList[j].useYN = 1;
					break;
				}

			}
		}

		if(j==tCnt)
		{
			fprintf(resultfp, "%s_C\n",  stSourceList[i].fileName);
		}
	}

	for(j=0; j<tCnt; j++)
	{
		if(stTargetList[j].useYN ==0)
		{
			fprintf(resultfp, "%s_D\n", stTargetList[j].fileName);
		}
	}

	if(resultfp)
	{
		fclose(resultfp);
	}
	return 0;
}

int readDirectory(char *inputPath)
{
	DIR *dir;
	struct dirent *ent;
	char pathBuf[20] ={0,};
	char pathBuf2[20]={0,};
	char vers[10] ={0,};
	FILE *rfp;
	FILE *wfp;

	dir = opendir(inputPath);

	sprintf(pathBuf2, "%s/%s", inputPath, "file_list.txt");
	wfp = fopen(pathBuf2, "w");

	if(dir != NULL)
	{
		while((ent=readdir(dir)) != NULL)
		{
			if(strstr(ent->d_name, ".txt") != NULL)
			{
				if(strcmp(ent->d_name, "file_list.txt") != 0)
				{
					sprintf(pathBuf, "%s/%s", inputPath, ent->d_name);
					rfp = fopen(pathBuf, "r");
					fgets(vers, 20, rfp);
					fprintf(wfp, "%s_%s", ent->d_name, vers);

					if(rfp)
					{
						fclose(rfp);
					}
				}
			}
		}
		closedir(dir);
	}
	else
	{
		perror("");
		return EXIT_FAILURE;
	}

	if(wfp)
	{
		fclose(wfp);
	}
	return 0;
}
