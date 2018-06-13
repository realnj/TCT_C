#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>
#include "./client.h"


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

void *receiveFile();
int getLineCount(int nStartLine);
void getFullPath(char *path, char *name, char *fullpath);

int nMode;
char key[1024];

int main(int ac, char **argv)
{
	pthread_t thread;
	int status;

	if(ac !=2)
	{
		printf("SP_TEST.EXE [ACK|ERR|NUM]");
		return 0;
	}

	if(strcmp(argv[1], "ACK")==0)
	{
		nMode = 1;
	}
	else if(strcmp(argv[1], "ERR")==0)
	{
		nMode = 2;
	}
	else if(strcmp(argv[1], "NUM")==0)
	{
		nMode = 3;
	}
	else if(strlen(argv[1])>0)
	{
		nMode = 4;
		memset(key, 0x00, sizeof(key));
		memcpy(key, argv[1], strlen(argv[1]));
	}
	else
	{
		printf("SP_TEST.EXE [ACK|ERR|NUM]");
		return 0;
	}

	connectServer("client");
	pthread_create(&thread, NULL, receiveFile, NULL);

	pthread_join(thread, (void**)&status);
	return 0;
}

void *receiveFile()
{
	char buf[1024]={0,};
	char buf2[1024]={0,};
	int totalCount = getLineCount(1);

	send_message("ABCDFILE.TXT");

	if(nMode == 4)
		send_message(key);

	bool isSendNak = false;
	bool isSendNum = false;
	int count = 0;

	while(1)
	{
		memset(buf, 0x00, sizeof(buf));

		if(recv_message(buf)>0)
		{
			if(nMode ==2 && count == (totalCount/2)&&(isSendNak==false))
			{
				send_message("ERR");
				isSendNak = true;
			}
			else if(nMode ==3 && count == (totalCount/2)&&(isSendNum==false)) //NUM
			{
				memset(buf2, 0x00, sizeof(buf2));
				sprintf(buf2, "%d", (totalCount/3));
				send_message(buf2);
				totalCount = getLineCount(totalCount/3);
				count = 0;
				isSendNum = true;
			}
			else
			{
				send_message("ACK");
				count++;
			}
		}
		if(totalCount == count)
			break;
	}
}

int getLineCount(int nStartLine)
{
	char fullPath[1024] ={0,};
	char line[1024] ={0,};
	char prevLine[1024]={0,};
	int count = 0;
	int nLineCount =0;
	char *line_p;

	getFullPath("BIGFILE", "ABCDFILE.TXT", fullPath);
	FILE *fp = fopen(fullPath, "r");

	if(fp != NULL)
	{
		while(!feof(fp))
		{
			fgets(line, sizeof(line), fp);

			if(nStartLine <= nLineCount+1)
			{
				if((line_p = strchr(line, '\r')) != NULL)
					*line_p = '\0';
				if((line_p = strchr(line, '\n')) != NULL)
					*line_p = '\0';
				if(strcmp(line, prevLine)!= 0)
					count++;

				memset(prevLine, 0x00, sizeof(prevLine));
				memcpy(prevLine, line, sizeof(line));
			}
			nLineCount++;
		}
	}

	fclose(fp);
	return count;
}

void getFullPath(char *path, char *name, char *fullpath)
{
	DIR *dir;
	struct stat st;
	char newPath[1024] ={0,};
	struct dirent *ent;
	dir = opendir(path);

	if(dir != NULL)
	{
		while((ent = readdir(dir)) != NULL)
		{
			lstat(ent->d_name, &st);
			if(strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0)
				continue;

			if(ent->d_type != 4)
			{
				//printf("file[%s]\n", ent->d_name);
				if(strcmp(ent->d_name, name)==0)
				{
					sprintf(fullpath, "%s/%s", path, ent->d_name);
					break;
				}
			}
			else
			{
//				printf("dir[%s]\n", ent->d_name);
				sprintf(newPath, "%s/%s", path, ent->d_name);
				getFullPath(newPath, name, fullpath);
			}
		}
		closedir(dir);
	}
	else
	{
		return;
	}
}
