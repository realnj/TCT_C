#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int readSourceFile(char *path);
int compressSourceStr(char *src, char *des);

// 맨 뒤에 0d0a 없는 파
int main(void)
{
	char *sPath = "source.txt"; // 맨 뒤에 0d0a 없는 파일
	char *tPath = "target.txt"; // 맨 뒤에 0d0a 있는 파일
//	readSourceFile(sPath);
//	readTargetFile(tPath);
	int count =getLineCount(1);
	printf("count = %d\n", count);
}

int getLineCount(int nStartLine)
{
	char fullPath[1024] ={0,};
	char line[1024] ={0,};
	char prevLine[1024]={0,};
	int count = 0;
	int nLineCount =0;
	char *line_p;

//	getFullPath("BIGFILE", "ABCDFILE.TXT", fullPath);
	FILE *fp = fopen("target.txt", "r");

	if(fp != NULL)
	{
		while(!feof(fp))
		{
//			memset(line, 0x00, sizeof(line));
			if(fgets(line, sizeof(line), fp) ==NULL)
			{
//				break;
			}
			if(nStartLine <= nLineCount+1)
			{
				if((line_p = strchr(line, '\r')) != NULL)
					*line_p = '\0';
				if((line_p = strchr(line, '\n')) != NULL)
					*line_p = '\0';
				if(strcmp(line, prevLine)!= 0)
				{
					count++;
					printf("//count = %d\n", count);
				}

				memset(prevLine, 0x00, sizeof(prevLine));
				memcpy(prevLine, line, sizeof(line));
			}
			nLineCount++;
//			printf("nLineCount = %d\n", nLineCount);
		}
	}

	fclose(fp);
	return count;
}

int compressSourceStr(char *src, char *des)
{
	int i=0;
	int j=0;
	int cnt =1;
	char prevStr=0;
	char result[100] ={0,};
	char buf[100]={0,};

	while(src[i])
	{
		memset(buf, 0x00, sizeof(buf));

		if(src[i]==prevStr)
		{
			 cnt++;
			 printf("same cnt = %d\n", cnt);
		}
		else
		{
			if(cnt >2)
			{
				sprintf(buf, "%d%c", cnt, prevStr);
				printf("[cnt >2] buf = %s\n", buf);
				memcpy(&result[j], buf, strlen(buf));
				j+= strlen(buf);
				cnt =1;
			}
			else if(cnt ==2)
			{
				sprintf(buf, "%c%c", prevStr, prevStr);
				printf("[cnt == 2] buf = %s\n", buf);
				memcpy(&result[j], buf, strlen(buf));
				j+=2;
				cnt =1;
			}
			else
			{
				if(i != 0)
				{
					result[j] = prevStr;
					printf("[cnt == 1] result[%d]  = %c\n", j, result[j]);
					j++;
				}
			}
		}

		prevStr = 0;
		prevStr = src[i];
		i++;
	}
	memset(buf, 0x00, sizeof(buf));

	if(cnt >2)
	{
		sprintf(buf, "%d%c", cnt, prevStr);
		printf("///[cnt >2] buf = %s\n", buf);
		memcpy(&result[j], buf, strlen(buf));
		j+= strlen(buf);
		cnt =1;
	}
	else if(cnt ==2)
	{
		sprintf(buf, "%c%c", prevStr, prevStr);
		printf("///[cnt == 2] buf = %s\n", buf);
		memcpy(&result[j], buf, strlen(buf));
		j+=2;
		cnt =1;
	}
	else
	{
		result[j] = prevStr;
		printf("///[cnt == 1] result[%d]  = %c\n", j, result[j]);
	}


	strcpy(des, &result[0]);
	printf("des = %s\n", des);
}

int readSourceFile(char *path)
{
	int i=0;
	FILE *rfp;
	FILE *wfp;
	int cnt =1;
	int readCnt=0;
	char prevStr[100]={0,};
	char readBuf[100]={0,};
	char changeBuf[100]={0,};
	char *line_p;
	rfp = fopen(path, "r");
	wfp = fopen("./sourceResult.txt", "w");

	while(fgets(readBuf, 100, rfp) != NULL)
	{
//		fgets(readBuf, 100, rfp);
//		printf("prevStr = [%s]\n", prevStr);
		if((line_p = strchr(readBuf, '\r')) != NULL)
			*line_p = '\0';
		if((line_p = strchr(readBuf, '\n')) != NULL)
			*line_p = '\0';

		printf("readBuf = [%s]\n", readBuf);
		compressSourceStr(readBuf, changeBuf);
		printf("changeBuf = [%s]\n", changeBuf);

		if(strcmp(prevStr, changeBuf)==0)
		{
			cnt++;
//			printf("same cnt = %d\n", cnt);
		}
		else
		{
			if(cnt > 1)
			{
				fprintf(wfp, "%d#%s\n", cnt, prevStr);
//				printf("cnt > 1 prevStr = %s\n", prevStr);
				cnt =1;
			}
			else
			{
				// cnt == 1
				if(readCnt !=0)
				{
					fprintf(wfp, "%s\n", prevStr);
//					printf("cnt == 1 prevStr = %s\n", prevStr);
				}
			}

		}
		memset(prevStr, 0x00, sizeof(prevStr));
		strcpy(prevStr, changeBuf);
		readCnt++;
//		printf("readCnt = %d\n", readCnt);
	}

	if(cnt >1)
	{
//		printf("here prevStr = [%s]\n", prevStr);
//		printf("here readBuf = [%s]\n", readBuf);
		fprintf(wfp, "%d#%s\n", cnt, prevStr);
	}
	else
	{
//		printf("here2 prevStr = [%s]\n", prevStr);
//		printf("here3 readBuf = [%s]\n", readBuf);
		fprintf(wfp, "%s\n", prevStr);
	}
//	printf("///readCnt = %d\n", readCnt);
	if(rfp)
	{
		fclose(rfp);
	}


}


int readTargetFile(char *path)
{
	int i=0;
	FILE *rfp;
	FILE *wfp;
	int cnt =1;
	int readCnt=0;
	char prevStr[100]={0,};
	char readBuf[100]={0,};
	char changeBuf[100] ={0,};
	char *line_p;
	rfp = fopen(path, "r");
	wfp = fopen("./targetResult.txt", "w");

	while(fgets(readBuf, 100, rfp) != NULL)
	{
		printf("prevStr = [%s]\n", prevStr);
		printf("readBuf = [%s]\n", readBuf);

		compressTargetStr(readBuf, changeBuf);
		if(strcmp(prevStr, changeBuf)==0)
		{
			cnt++;
			printf("same cnt = %d\n", cnt);
		}
		else
		{
			if(cnt > 1)
			{
				fprintf(wfp, "%d#%s", cnt, prevStr);
				printf("cnt > 1 prevStr = %s\n", prevStr);
				cnt =1;
			}
			else
			{
				// cnt == 1
				if(readCnt !=0)
				{
					fprintf(wfp, "%s", prevStr);
					printf("cnt == 1 prevStr = %s\n", prevStr);
				}
			}

		}
		memset(prevStr, 0x00, sizeof(prevStr));
		strcpy(prevStr, changeBuf);
		readCnt++;
	}

	if(cnt >1)
	{
		fprintf(wfp, "%d#%s", cnt, prevStr);
	}
	else
	{
		fprintf(wfp, "%s", prevStr);
	}

	if(rfp)
	{
		fclose(rfp);
	}


}
int compressTargetStr(char *src, char *des)
{
	int i=0;
	int j=0;
	int cnt =1;
	char prevStr=0;
	char result[100] ={0,};
	char buf[100]={0,};

	while(src[i])
	{
		memset(buf, 0x00, sizeof(buf));

		if(src[i]==prevStr)
		{
			 cnt++;
			 printf("same cnt = %d\n", cnt);
		}
		else
		{
			if(cnt >2)
			{
				sprintf(buf, "%d%c", cnt, prevStr);
				printf("[cnt >2] buf = %s\n", buf);
				memcpy(&result[j], buf, strlen(buf));
				j+= strlen(buf);
				cnt =1;
			}
			else if(cnt ==2)
			{
				sprintf(buf, "%c%c", prevStr, prevStr);
				printf("[cnt == 2] buf = %s\n", buf);
				memcpy(&result[j], buf, strlen(buf));
				j+=2;
				cnt =1;
			}
			else
			{
				if(i != 0)
				{
					result[j] = prevStr;
					printf("[cnt == 1] result[%d]  = [%02X]\n", j, result[j]);
					j++;
				}
			}
		}

		prevStr = 0;
		prevStr = src[i];
		i++;
	}

	strcpy(des, &result[0]);
	printf("des = [%s]\n", des);
}
