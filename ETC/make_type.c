#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct item
{
	char code[2];
	char del;
	char date[14];
	char del2;
	char msg[9];
	char tmp[2];
}ITEM;

typedef struct type
{
	char type[2];
	int count;
}TYPE;

TYPE typeList[10];
ITEM stItem[100];

int nCountType;
int nCount;

void readLogFile();
void printTypeInfo();
void enrollType();

int main(void)
{
	readLogFile();
	enrollType();
	printTypeInfo();
}


 void readLogFile()
{
	FILE *fp;
	char str[100]={0,};

	fp = fopen("./itemlist.txt", "r");

	while(fgets(str, 100, fp) != NULL)
	{
		memcpy(&stItem[nCount].code, &str[0], 2);
		memcpy(&stItem[nCount].date, &str[3], 14);
		memcpy(&stItem[nCount].msg, &str[18], 9);

//		printf("stItem[%d].code %.2s\n", i, stItem[i].code);
//		printf("stItem[%d].date %.14s\n", i, stItem[i].date);
//		printf("stItem[%d].msg %s\n", i, stItem[i].msg);

		nCount++;
	}

	if(fp)
	{
		fclose(fp);
	}
}

void enrollType()
{
	int i;

	for(int j=0; j<nCount; j++)
	{
		for(i=0;i<nCountType;i++)
		{
			if(memcmp(typeList[i].type,stItem[j].code,2)==0)
			{
				typeList[i].count++;
				break;
			}
		}
		if( i == nCountType)
		{
			memcpy(typeList[i].type, stItem[j].code, strlen(stItem[j].code));
			typeList[i].count =1;
			nCountType++;
		}
	}

}

void printTypeInfo()
{
	printf("===============\n");
	for(int i=0;i<nCountType;i++)
	{
		printf("%.2s: %d\n",typeList[i].type, typeList[i].count);
	}
}

