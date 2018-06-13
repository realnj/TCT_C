#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "./server.h"


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

int compressFile(char *path, char *fileName);
int compressStr(char *src, char *des);
int changeStr(char *src, char *des);
void sendFile();
void getFullPath(char *path, char *name, char *fullpath);

int main()
{
	connectServer();
	sendFile();
	return 0;
}

void sendFile()
{
	char fullPath[1024]={0,};
	char buf[1024]={0,};
	char readBuf[1024]={0,};
	char changeBuf[1024]={0,};
	char sendBuf[1024]={0,};
	char line[1024]={0,};
	char prevLine[1024]={0,};
	char *line_p = NULL;
	int readCnt =0;
	int flag =0;
	int cnt =1;
	FILE *fp;

	if(recv_message(buf)<=0)
	{
		printf("exit\n");
		return;
	}

	getFullPath("BIGFILE", buf, fullPath);

	memset(buf, 0x00, sizeof(buf));

	fp = fopen(fullPath, "r");

	if(fp != NULL)
	{
		while(!feof(fp))
		{
			memset(readBuf, 0x00, sizeof(readBuf));
			memset(sendBuf, 0x00, sizeof(sendBuf));
			memset(line, 0x00, sizeof(line));
			fgets(readBuf, sizeof(readBuf), fp);

			changeStr(readBuf, changeBuf);
			compressStr(changeBuf, line);

			if((line_p = strchr(line, '\r')) != NULL)
				*line_p = '\0';
			if((line_p = strchr(line, '\n')) != NULL)
				*line_p = '\0';

			if(strcmp(line, prevLine)==0)
			{
				cnt++;
			}
			else
			{
				if(cnt > 1)
				{
					sprintf(sendBuf, "%d#%s", cnt, prevLine);
					flag = 1;
				}
				else
				{
					if(readCnt != 0)
					{
						memcpy(sendBuf, prevLine, strlen(prevLine));
						flag = 1;
					}
				}
			}
			memset(prevLine, 0x00, sizeof(prevLine));
			memcpy(prevLine, line, strlen(line));

			if(readCnt != 0 && flag ==1)
			{
				send_message(sendBuf);
				cnt =1;
				flag = 0;
				if(recv_message(buf) > 0)
				{
						if(strcmp(buf, "ACK")==0)
						{
							printf("receive ACK\n");
						}
						else if(strcmp(buf, "ERR")==0)
						{
							printf("receive ERR\n");

							while(1)
							{
								send_message(sendBuf);
								if(recv_message(buf)>0)
								{
									if(strcmp(buf, "ACK")==0)
									{
										printf("receive ACK\n");
										break;
									}
								}
							}
						}
						else
						{
							fclose(fp);
							readCnt =0;
							memset(prevLine, 0x00, sizeof(prevLine));
							fp = fopen(fullPath, "r");
							for(int i=0; i<atoi(buf)-1; i++)
							{
								fgets(readBuf, sizeof(readBuf), fp);
							}
							memset(sendBuf, 0x00, sizeof(sendBuf));
							continue;
						}
				} // recv_message
				memset(sendBuf, 0x00, sizeof(sendBuf));
			} // send_message
			readCnt++;
		} // feof
	} // fp != NULL

	fclose(fp);
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
		changeStr(readBuf, changeBuf);
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
				if(i != 0)
				{
					resultBuf[j] = prevStr;
					j++;
				}
			}
			cnt =1;
		}
		prevStr = 0;
		prevStr = src[i];
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
				if(strcmp(ent->d_name, name)==0)
				{
					sprintf(fullpath, "%s/%s", path, ent->d_name);
					break;
				}
			}
			else
			{
				sprintf(newPath, "%s/%s", path, ent->d_name);
				getFullPath(newPath, name, fullpath);
			}
		}
		closedir(dir);
	}
	else
	{
		return NULL;
	}
}
