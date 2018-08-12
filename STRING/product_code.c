#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

#define PRODUCT_TYPE_NUM 13
#define MAX_KIND 500
#define MAX_DISTINCTION_KIND 100
#define MAX_TEXT_LENGTH 20

char products[PRODUCT_TYPE_NUM][MAX_TEXT_LENGTH] =
{
		"coffee", "gimbap", "water", "ramen", "kinchi", "rice", "cigarettes",
		"milk", "chocolate", "paper", "soju", "beer"
};
int saleNumber = 0; // �Ǹŵ� ��ǰ�� ����
char saleKind[MAX_KIND][MAX_TEXT_LENGTH];

char distinctionKind[MAX_DISTINCTION_KIND][MAX_TEXT_LENGTH];
int distinctionNumber =0;// ���е� ����

void loadData();
void printData(char kind[][MAX_TEXT_LENGTH], int count);
void makeNormalData(char retData[][MAX_TEXT_LENGTH], char saleKind[][MAX_TEXT_LENGTH], int saleNumber);
void correctLetterOrder(char retData[][MAX_TEXT_LENGTH], char saleKind[][MAX_TEXT_LENGTH],  int saleNumber, char products[][MAX_TEXT_LENGTH]);
void makeDistinctedData(char retData[][MAX_TEXT_LENGTH], char saleKind[][MAX_TEXT_LENGTH], int saleNumber);

int main(void)
{
	char saleKind_returnData[MAX_KIND][MAX_TEXT_LENGTH];
	char distinctionKind_returnData[MAX_KIND][MAX_TEXT_LENGTH];
	int i=0;

	loadData();
	// ���� ���
	printf("(0) ���� �Ǹŵ� ��ǰ ���\n");
	printData(saleKind, saleNumber);

	// 1. Ư������ �� ���� ���� �� �ҹ��ڷ�
	makeNormalData(saleKind_returnData, saleKind, saleNumber);
	memcpy(saleKind, saleKind_returnData, sizeof(saleKind));
	printf("(1) Ư������ �� ���� ���� �� �ҹ��ڷ�");
	printData(saleKind, saleNumber);

	// 2. ��ǰ�� �̸��� �ٷ� ��´�.
	correctLetterOrder(saleKind_returnData, saleKind, saleNumber, products);
	memcpy(saleKind, saleKind_returnData, sizeof(saleKind));
	printf("(2) ������ ������ ������ ��� \n");
	printData(saleKind, saleNumber);

	// 3. �ߺ��� ����� �����Ѵ�.
	makeDistinctedData(distinctionKind_returnData, saleKind, saleNumber);
	memcpy(distinctionKind, distinctionKind_returnData, sizeof(distinctionKind));

	for(i=0; i<MAX_DISTINCTION_KIND; i++)
	{
		if(distinctionKind[i][0] != '\0')
		{
			distinctionNumber++;
		}
	}
	printf("(3) �ߺ� ��� �����ϰ� ������ ���\n");
	printData(distinctionKind, distinctionNumber);
}

void loadData()
{
	memset(saleKind, 0, sizeof(saleKind));
	saleNumber = 20;
	char data[MAX_KIND][20] ={"coffee", "eeFFCo", "amenr", "Ra Men", "CO FFE E",
			"coFfee", "c#off$ee", "cOe f%%&f*e", "bapgim", "rice", "RiCE", "*Ri&c@e",
			"gim $bap", "BAP@gim", "G*imba p", "water", "FFCOEE", "WATER", "TERAW", "*tW$a ER#"
	};

	memcpy(saleKind, data, sizeof(data));
}

void makeNormalData(char retData[][MAX_TEXT_LENGTH], char saleKind[][MAX_TEXT_LENGTH], int saleNumber)
{

	int i=0;
	int j=0;
	int m=0;
	memset(retData, '\0', sizeof(char) * MAX_TEXT_LENGTH * MAX_KIND);
	for(i=0; i<saleNumber; i++)
	{
		strlwr(saleKind[i]);
		m=0;
		for(j=0; j<strlen(saleKind[i]); j++)
		{
			if(saleKind[i][j] >='a' && saleKind[i][j] <='z')
			{
				retData[i][m] = saleKind[i][j];
				m++;
			}
		}
	}
}

void correctLetterOrder(char retData[][MAX_TEXT_LENGTH], char saleKind[][MAX_TEXT_LENGTH],  int saleNumber, char products[][MAX_TEXT_LENGTH])
{
	memset(retData, '\0', sizeof(char)*MAX_TEXT_LENGTH);
	int i, j=0;
	int m, n=0;
	int len=0;
	int check[20]={0,};

	for(i=0; i<saleNumber; i++)
	{
		for(m=0; m<PRODUCT_TYPE_NUM; m++)
		{
			len =0;
			if(strlen(saleKind[i]) != strlen(products[m]))
			{
				continue;
			}

			for(n=0; n<strlen(products[m]); n++)
			{
				for(j=0; j<strlen(saleKind[i]); j++)
				{
					if(products[m][n] == saleKind[i][j] && check[j]==0)
					{
						check[j] =1;
						len++;
						break;
					}
				}
			}

			memset(check, 0x00, sizeof(check));
			if(len == strlen(products[m]))
			{
				strcpy(retData[i], products[m]);
				len = 0;
				break;
			}

		}
	}
}

void makeDistinctedData(char retData[][MAX_TEXT_LENGTH], char saleKind[][MAX_TEXT_LENGTH],  int saleNumber)
{
	memset(retData, '\0', sizeof(char)*MAX_TEXT_LENGTH);
	int i, j=0;
	int typeCount =0;
	char tmp[10]={0,};

	for(i=0; i<saleNumber; i++)
	{
		for(j=0; j<typeCount; j++)
		{
			if(memcmp(retData[j], saleKind[i], strlen(saleKind[i]))==0)
			{
				break;
			}
		}

		if(j==typeCount)
		{
			memcpy(retData[typeCount], saleKind[i], strlen(saleKind[i]));
			typeCount++;
		}
	}

	for(i=0; i<typeCount-1; i++)
	{
		for(j=0; j<typeCount-1-i; j++)
		{
			if(retData[j][1] > retData[j+1][1])
			{
				strcpy(tmp, retData[j]);
				strcpy(retData[j], retData[j+1]);
				strcpy(retData[j+1], tmp);
			}
			else if(retData[j][1] == retData[j+1][1])
			{
				if(retData[j][0] > retData[j+1][0])
				{
					strcpy(tmp, retData[j]);
					strcpy(retData[j], retData[j+1]);
					strcpy(retData[j+1], tmp);
				}
			}
		}
	}
}

void printData(char kind[][MAX_TEXT_LENGTH], int count)
{
	int i;

	printf("-------------------\n");
	printf("��ǰ ����\n");
	printf("-------------------\n");
	for(i=0; i<count; i++)
	{
		printf("%s \n", kind[i]);
	}
	printf("\n");
}
