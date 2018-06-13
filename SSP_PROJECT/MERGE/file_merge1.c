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
int readFileList();
int writeResultFile();

int main()
{
	char *sourcePath = "./source";
	char *targetPath = "./target";

	readDirectory(sourcePath);
	readDirectory(targetPath);

	readFileList();
	writeResultFile();
	updateTargetFile();

	return 0;
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

int readFileList()
{
	FILE *sfp;
	FILE *tfp;

	char buf[100] ={0,};
	char *token1 = NULL;
	char *token2 = NULL;

	sfp = fopen("./source/file_list.txt", "r");
	tfp = fopen("./target/file_list.txt", "r");

	while(fgets(buf, 100, sfp) != NULL)
	{
		token1 = strtok(buf, "_");
		strcpy(stSourceList[sCnt].fileName, token1);

		token2 = strtok(NULL, "_");
		stSourceList[sCnt].fileVers = atoi(token2);
		sCnt++;
	}

	memset(buf, 0x00, 100);


	while(fgets(buf, 100, tfp) != NULL)
	{
		token1 = strtok(buf, "_");
		strcpy(stTargetList[tCnt].fileName, token1);

		token2 = strtok(NULL, "_");
		stTargetList[tCnt].fileVers = atoi(token2);
		tCnt++;
	}

	if(sfp)
	{
		fclose(sfp);
	}

	if(tfp)
	{
		fclose(tfp);
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
