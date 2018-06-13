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

int readFile(char *path, char *fileName);
int main()
{
	char fileName[256] ={0, };
	char *path = "./BIGFILE";

	printf("file name :\n");

	scanf("%s", fileName);

	readFile(path, fileName);

	return 0;

}

int readFile(char *path, char *fileName)
{
	FILE *rfp;
	FILE *wfp;
	int cnt =1;
	char pathBuf[256] ={0,};
	char writePathBuf[256] ={0,};
	char readBuf[256] ={0,};
	char prevBuf[256] ={0,};


	sprintf(pathBuf, "%s/%s", path, fileName);
	rfp = fopen(pathBuf, "r");

	sprintf(writePathBuf, "./%s", fileName);
	wfp = fopen(writePathBuf, "w");

	while(fgets(readBuf, 100, rfp) != NULL)
	{
		if(strcmp(prevBuf, readBuf)==0)
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

			strcpy(prevBuf, readBuf);
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

