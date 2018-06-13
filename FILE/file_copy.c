#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

int MyCopyFile(char *fname);

int main(void)
{
	struct dirent *de;
	char path[256] ={0,};
	int nFilesize = 0;
	struct stat st;

	DIR *dr = opendir("./INPUT");

	if( dr == NULL)
	{
		printf("Could not open current directory\n");
		return 0;
	}

	while((de = readdir(dr)) != NULL)
	{
		if(de->d_type != DT_REG)
		{
			printf("[%s]\n", de->d_name);
		}
		else
		{
			sprintf(path, "./INPUT/%s", de->d_name);
			stat(path, &st);
			nFilesize = st.st_size;
			printf("%s = %d\n", de->d_name, nFilesize);

			if(nFilesize > 1024)
			{
				MyCopyFile(de->d_name);
			}
		}
	}

	closedir(dr);
}


int MyCopyFile(char *fname)
{
	FILE *rfp;
	FILE *wfp;
	char fnameIn[50] ={0,};
	char fnameOut[50] = {0,};
	char buf[512] ={0,};
	int readLen =0;

	mkdir("./OUTPUT", 0777);

	sprintf(fnameIn, "./INPUT/%s", fname);
	sprintf(fnameOut, "./OUTPUT/%s", fname);

	rfp = fopen(fnameIn, "r");
	wfp = fopen(fnameOut, "w");

	while((readLen = fread(buf, 1, 512, rfp)) != 0)
	{
		fwrite(buf, 1, readLen, wfp);
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

