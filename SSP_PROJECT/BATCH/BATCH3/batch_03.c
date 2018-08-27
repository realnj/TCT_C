#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <error.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

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
int compare_func_des(const void *a, const void *b);
int writeResultFile();
int isExistProgram(char *fileName);

int main(void)
{
	char str[100]={0,};
	CMD stTmp;
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
			//printCmdList();
			writeResultFile();
			break;
		}

		tokenCode = strtok(str, "#");

		if(tokenCode[0] == 'C')
		{
			tokenName = strtok(NULL, "#");

			if(isExistProgram(tokenName) != 0)
			{
				printf("[C]BATCH ������ ����\n");
				continue;
			}

			for(i=0; i<nTotalCnt; i++)
			{
				if(memcmp(stCmd[i].progName, tokenName, strlen(tokenName))==0)
				{
					break;
				}
			}

			if(i !=nTotalCnt)
			{
				printf("[C]�̹� ���α׷��� ����\n");
				continue;
			}

			stCmd[nTotalCnt].code = 'C';
			memcpy(stCmd[nTotalCnt].progName, tokenName, strlen(tokenName));
			tokenGap = strtok(NULL, "#");
			stCmd[nTotalCnt].progGap = atoi(tokenGap);
			tokenTime = strtok(NULL, "#");
			stCmd[nTotalCnt].progTime = atoi(tokenTime);
			nTotalCnt++;

			if(checkProgramCount() >5)
			{
				stCmd[nTotalCnt].code = 0;
				memset(stCmd[nTotalCnt].progName, 0x00, sizeof(stCmd[nTotalCnt].progName));
				stCmd[nTotalCnt].progGap = 0;
				stCmd[nTotalCnt].progTime=0;
				nTotalCnt--;
				continue;
			}
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
						stTmp = stCmd[i];

						stCmd[i].code = 'U';
						memcpy(stCmd[i].progName, tokenName, strlen(tokenName));
						tokenGap = strtok(NULL, "#");
						stCmd[i].progGap = atoi(tokenGap);
						tokenTime = strtok(NULL, "#");
						stCmd[i].progTime = atoi(tokenTime);

						if(checkProgramCount() >5)
						{
							stCmd[i] = stTmp;
							printf("[U] update ����\n");
						}
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
				printf("[D]���� ���α׷��� ����\n");
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

			for(i=0; i<nTotalCnt; i++)
			{
				stCmd[i] = stTmpCmd[i];
			}

		}

	}
}

int checkProgramCount()
{
	int count=0;
	int i, j=0;
	int arr[20][20]={0,};
	int m=0;
	int sum[20]={0,};
	int maxSum=0;
	for(i=0; i<nTotalCnt; i++)
	{
		for(j=stCmd[i].progGap; j<20; j+=stCmd[i].progGap)
		{
			for(m=j; m<j+stCmd[i].progTime&&m<20; m++)
			{
				arr[i][m] +=1;
			}
		}
	}

	for(i=0; i<20; i++)
	{
		for(j=0; j<20; j++)
		{
//			printf("[%d] ", arr[i][j]);
			sum[j] += arr[i][j];
		}
//		printf("\n");
	}


	for(j=0; j<20; j++)
	{
		if(maxSum < sum[j])
		{
			maxSum = sum[j];
		}
	}
	return maxSum;
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

	qsort(stCmd, nTotalCnt, sizeof(CMD), compare_func_des);

	for(i=0; i<nTotalCnt; i++)
	{
		printf("%s\n", stCmd[i].progName);
		fprintf(fp, "%s#%d#%d\n", stCmd[i].progName, stCmd[i].progGap, stCmd[i].progTime);
	}

	if(fp)
	{
		fclose(fp);
	}

	return 0;
}

int compare_func_des(const void *a, const void *b)
{
	CMD *left = (CMD *)a;
	CMD *right = (CMD *)b;

	if(left->progGap <right->progGap)
	{
		return 1;
	}
	else if(left->progGap > right->progGap)
	{
		return -1;
	}
	else
	{
		 return strcmp( right->progName , left->progName );
	}
}

int isExistProgram(char *fileName)
{
	  DIR *dir;
	  struct dirent *ent;
	  int result =1;
	  dir = opendir ("./BATCH");
	  if (dir != NULL) {

			  /* print all the files and directories within directory */
			  while ((ent = readdir (dir)) != NULL) {
				  //���ϸ� .log ���Ե� ���
				  	  if(strstr(ent->d_name,".EXE")!= NULL)
				  	  {
				  		  printf ("%s\n", ent->d_name);
				  		  if(strcmp(fileName, ent->d_name)==0)
				  		  {
				  			  result =0;
				  			  return result;
				  		  }
				  	  }
			  }
			  closedir (dir);
	  } else {
			  /* could not open directory */
			  perror ("");
			  return EXIT_FAILURE;
	  }

	  return result;
}
