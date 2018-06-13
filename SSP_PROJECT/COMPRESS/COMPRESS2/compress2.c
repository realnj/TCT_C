#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <glib.h>


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

int compressFile(char *path, char *fileName);
int compressStr(char *src, char *des);

int main()
{
	char fileName[256] ={0, };
	char *path = "./BIGFILE";

	printf("file name :\n");

	scanf("%s", fileName);

	compressFile(path, fileName);

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
	char outBuf[256] ={0,};

	sprintf(pathBuf, "%s/%s", path, fileName);
	rfp = fopen(pathBuf, "r");

	sprintf(writePathBuf, "./%s", fileName);
	wfp = fopen(writePathBuf, "w");

	while(fgets(readBuf, 100, rfp) != NULL)
	{

		compressStr(readBuf, outBuf);

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
		printf("src[%d] = %c\n", i, src[i]);
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

}
