#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

//06:00

typedef struct cmd
{
	char code;
	char progName[20];
	int progGap;
	int progTime;
}CMD;

CMD stCmd[30];
CMD stTmpCmd[30];
int nTotalCnt;

void printCmdList();
int main(void)
{
	char str[100]={0,};
	char *tokenCode;
	char *tokenName;
	char *tokenGap;
	char *tokenTime;
	int i=0;
	int j=0;
	int deletePos =0;

	while(1)
	{
		scanf("%s", str);

		if(str[0] == 'P' && strlen(str)==1)
		{
			printf("exit\n");
			printCmdList();
			writeResultFile();
			break;
		}

		tokenCode = strtok(str, "#");

		if(tokenCode[0] == 'C')
		{
			tokenName = strtok(NULL, "#");
			for(i=0; i<nTotalCnt; i++)
			{
				if(memcmp(stCmd[i].progName, tokenName, strlen(tokenName))==0)
				{
					break;
				}
			}

			if(i !=nTotalCnt)
			{
				printf("[C]이미 프로그램이 있음\n");
				continue;
			}

			stCmd[nTotalCnt].code = 'C';
			memcpy(stCmd[nTotalCnt].progName, tokenName, strlen(tokenName));
			tokenGap = strtok(NULL, "#");
			stCmd[nTotalCnt].progGap = atoi(tokenGap);
			tokenTime = strtok(NULL, "#");
			stCmd[nTotalCnt].progTime = atoi(tokenTime);
			nTotalCnt++;
		}
		else if(tokenCode[0] == 'U')
		{
			tokenName = strtok(NULL, "#");
			for(i=0; i<nTotalCnt; i++)
			{
				if(memcmp(stCmd[i].progName, tokenName, strlen(tokenName))==0)
				{
					if(stCmd[i].code == 'C')
					{
						stCmd[i].code = 'U';
						memcpy(stCmd[i].progName, tokenName, strlen(tokenName));
						tokenGap = strtok(NULL, "#");
						stCmd[i].progGap = atoi(tokenGap);
						tokenTime = strtok(NULL, "#");
						stCmd[i].progTime = atoi(tokenTime);
						break;
					}
				}
			}

		}
		else if(tokenCode[0] == 'D')
		{
			tokenName = strtok(NULL, "#");
			for(i=0; i<nTotalCnt; i++)
			{
				if(memcmp(stCmd[i].progName, tokenName, strlen(tokenName))==0)
				{
					deletePos = i;
					break;
				}
			}

			if(i==nTotalCnt)
			{
				printf("[D]지울 프로그램이 없음\n");
				continue;
			}

			for(i=0; i<nTotalCnt; i++)
			{
				if(deletePos!=i)
				{
					stTmpCmd[j] = stCmd[i];
					j++;
				}
			}
			nTotalCnt--;
			printf("nTotalCnt=%d\n", nTotalCnt);
			for(i=0; i<nTotalCnt; i++)
			{
				stCmd[i] = stTmpCmd[i];
			}

		}

	}
}

void printCmdList()
{
	int i=0;

	for(i=0; i<nTotalCnt; i++)
	{
		printf("stCmd[%d].code =%c\n", i, stCmd[i].code);
		printf("stCmd[%d].progName =%s\n", i, stCmd[i].progName);
		printf("stCmd[%d].progGap =%d\n", i, stCmd[i].progGap);
		printf("stCmd[%d].progTime =%d\n", i, stCmd[i].progTime);
	}
}



int writeResultFile()
{
	int i=0;
	FILE *fp;

	fp = fopen("./OUTFILE/result.txt", "w");

	for(i=0; i<nTotalCnt; i++)
	{
		printf("%s\n", stCmd[i].progName);
		fprintf(fp, "%s#%d#%d\n", stCmd[i].progName, stCmd[i].progGap, stCmd[i].progTime);
	}

	if(fp)
	{
		fclose(fp);
	}
}
