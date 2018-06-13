#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <glib.h>


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

int compressFile(char *path, char *fileName);
int compressStr(char *src, char *des);
int scanDirectory(char *inputPath, char *fileName);

int main()
{
	char fileName[256] ={0, };
	char *path = "./BIGFILE";
	int result =0;
	printf("file name :\n");

	scanf("%s", fileName);

	result = scanDirectory(path, fileName);

	return result;

}

int scanDirectory(char *inputPath, char *fileName)
{
	DIR *dir = NULL;
	struct dirent *entry = NULL;
	struct stat statBuf;
	char pathBuf[100]={0,};

	if( (dir = opendir(inputPath)) == NULL)
	{
		printf("cannot open directory\n");
		return -1;
	}

	while((entry=readdir(dir))!= NULL)
	{
		if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0)
		{
			continue;
		}
//		printf("%s\n", entry->d_name);

		sprintf(pathBuf, "%s/%s", inputPath, entry->d_name);
		stat(pathBuf, &statBuf);

		if(S_ISDIR(statBuf.st_mode))
		{
			printf("1. Directory : %s\n", entry->d_name);
			scanDirectory(pathBuf, fileName);
		}
		else if(S_ISREG(statBuf.st_mode))
		{
			printf("2. FILE : %s\n", entry->d_name);
			if(strcmp(entry->d_name, fileName)==0)
			{
				printf("Find File\n");
				compressFile(inputPath, fileName);
			}
		}

	}

	closedir(dir);
	return 0;

}

int compressFile(char *path, char *fileName)
{
	FILE *rfp;
	FILE *wfp;
	int cnt =1;
	char pathBuf[256] ={0,};
	char writePathBuf[256] ={0,};
	char readBuf[256] ={0,};
	char prevBuf[256] ={0,};
	char changeBuf[256] ={0,};
	char outBuf[256] ={0,};

	sprintf(pathBuf, "%s/%s", path, fileName);
	rfp = fopen(pathBuf, "r");

	sprintf(writePathBuf, "./%s", fileName);
	wfp = fopen(writePathBuf, "w");

	while(fgets(readBuf, 100, rfp) != NULL)
	{
//		printf("(1)readBuf = %s\n", readBuf);
		changeStr(readBuf, changeBuf);

//		printf("(2)changeBuf = %s\n", changeBuf);
		compressStr(changeBuf, outBuf);

		if(strcmp(prevBuf, outBuf)==0)
		{
			cnt++;
		}
		else
		{
			if(cnt > 1)
			{
				fprintf(wfp, "%d#%s", cnt, prevBuf);
				cnt =1;
			}
			else
			{
				fprintf(wfp, "%s", prevBuf);
				cnt =1;
			}

			strcpy(prevBuf, outBuf);
		}

	}

	if(cnt > 1)
	{
		fprintf(wfp, "%d#%s", cnt, prevBuf);
		cnt =1;
	}
	else
	{
		fprintf(wfp, "%s", prevBuf);
		cnt =1;
	}

	if(rfp)
	{
		fclose(rfp);
	}

	if(wfp)
	{
		fclose(wfp);
	}

	return 0;
}

int compressStr(char *src, char *des)
{
	int i=0;
	int j=0;
	int cnt =1;
	char prevStr =0;
	char buf[100]={0,};
	char resultBuf[100]={0,};

	while(src[i])
	{
//		printf("src[%d] = %c\n", i, src[i]);
		if(src[i] == prevStr)
		{
			cnt++;
		}
		else
		{
			if(cnt > 2)
			{
				sprintf(buf, "%d%c", cnt, prevStr);

				memcpy(&resultBuf[j], buf, strlen(buf));
				j+=strlen(buf);

			}
			else if(cnt==2)
			{
				sprintf(buf, "%c%c", prevStr, prevStr);
				memcpy(&resultBuf[j], buf, 2);
				j+=2;

			}
			else
			{
				if(prevStr != 0)
				{
					resultBuf[j] = prevStr;
					j++;
				}
			}
			cnt =1;
			prevStr = src[i];
		}
		i++;

	}

	strcpy(des, resultBuf);
	return 0;
}

int changeStr(char *src, char *des)
{
	int i=0;

	while(src[i])
	{
		if(src[i]>=0x41 && src[i] <=0x45)
		{
			des[i] = src[i] + 26 - 5;
		}
		else if(src[i] == 0x0D ||src[i] == 0x0A )
		{
			des[i] = src[i];
		}
		else
		{
			des[i] = src[i]-5;
		}
		i++;
	}

	des[i]='\0';
	return 0;

}
