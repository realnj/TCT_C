#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

typedef struct code
{
	char typeName[3];
	char iter;
	char msg[10];

}CODE;

typedef struct type
{
	char abTypeName[3];
	int nCnt;
}TYPE;


CODE stCode;
TYPE stType[20];

int nTypeCnt;

void printMenu();
void writeEachLogFile(char *str);
int makeTypeList(char *type);
int inputMenuLoop();

int main(void)
{
	inputMenuLoop();
}

int inputMenuLoop()
{
	char str[100]={0,};

	while(1)
	{
		gets(str);

		if(memcmp(str, "q", 1)==0 || memcmp(str, "Q", 1)==0)
		{
			printf("QUIT PROGRAM\n");
			break;
		}

		printf("strlen(str) = %d\n", strlen(str));
		memcpy(&stCode, str, strlen(str));

		makeTypeList(stCode.typeName);
		writeEachLogFile(str);
	}

	return 0;
}

void writeEachLogFile(char *str)
{
	char fileName[20]={0,};
	int num =0;
	int i =0;
	FILE *fp;

	for(i=0; i<nTypeCnt; i++)
	{
		if(memcmp(stType[i].abTypeName, stCode.typeName, 3)==0)
		{
			num = (stType[i].nCnt-1)/3;
			sprintf(fileName, "%.3s_LOG%02d.txt", stCode.typeName, num);
			printf("num = %d\n", num);
			break;
		}
	}

	fp = fopen(fileName, "a+");

	fprintf(fp, "%s\n", str);

	if(fp)
	{
		fclose(fp);
	}
}

int makeTypeList(char *type)
{
	int i=0;

	for(i=0; i<nTypeCnt; i++)
	{
		if(memcmp(type, stType[i].abTypeName, 3)==0)
		{
			stType[i].nCnt++;
			break;
		}
	}

	if(i==nTypeCnt)
	{
		memcpy(stType[i].abTypeName, type, 3);
		stType[i].nCnt = 1;
		nTypeCnt++;
	}

	return 0;
}

void printMenu()
{
	printf("===============================\n");
	printf("=1. MESSAGE CODE                 =\n");
	printf("=2. Q : QUIT               			  =\n");
	printf("===============================\n");
}
