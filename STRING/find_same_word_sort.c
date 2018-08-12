#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
#define TYPE_NUM 12

char products[TYPE_NUM][20] =
{
		"coffee", "gimbap", "water", "ramen", "kinmchi", "rice", "cigarettes",
		"milk", "chocolate", "paper", "soju", "beer"
};

void printData(char kind[][20], int count);
int findSameWordSort(char retData[][20], char inputData[][20], char products[][20], int count);
int main(void)
{
	char inputData[50][20] ={"coffee", "eeffco", "amenr", "ramen", "eerb", "bapgim", "rice", "icer","perpa", "bapgim",
											"gimbap", "water", "ffcoee", "ilkm", "teraw", "twaer", "colatecho", "juso"}; //18개
	char returnData[50][20] ={0,};
	int count = 18;

	/* 정렬해서 체크 */
	findSameWordSort(returnData, inputData, products, count);
	printData(returnData, count);
	/* 정렬 안하고 체크 */
//	findSameWord();
}

int findSameWordSort(char retData[][20], char inputData[][20], char products[][20], int count)
{
	char sortedProducts[TYPE_NUM][20];
	int i, k, num=0;
	char prodStr[20]={0,};
	char tmpCh;

	memset(retData, '\0', sizeof(char)*20*50);
	memset(sortedProducts, '\0', sizeof(sortedProducts));
	memcpy(sortedProducts, products, sizeof(sortedProducts));

	for(num=0; num<TYPE_NUM; num++)
	{
		memset(prodStr, '\0', sizeof(prodStr));
		memcpy(prodStr, sortedProducts[num], sizeof(prodStr));

		for(i=0; i<strlen(prodStr)-1; i++)
		{
			for(k=i+1; k<strlen(prodStr); k++)
			{
				if(prodStr[i] > prodStr[k])
				{
					tmpCh = prodStr[i];
					prodStr[i] = prodStr[k];
					prodStr[k] = tmpCh;
				}
			}
		}

		memcpy(sortedProducts[num], prodStr, sizeof(prodStr));
	}

	// 목록의 각 단어들을 정렬된 단어와 같은지 체크해서 올바른 단어로 교체

	for(num=0; num<count; num++)
	{
		memset(prodStr, '\0', sizeof(prodStr));
		memcpy(prodStr, inputData[num], sizeof(prodStr));

		for(i=0; i<strlen(prodStr)-1; i++)
		{
			for(k=i+1; k<strlen(prodStr); k++)
			{
				if(prodStr[i] > prodStr[k])
				{
					tmpCh = prodStr[i];
					prodStr[i] = prodStr[k];
					prodStr[k] = tmpCh;
				}
			}
		}

		for(i=0; i<TYPE_NUM; i++)
		{
			if(!strcmp(prodStr, sortedProducts[i]))
			{
				memcpy(inputData[num], products[i], sizeof(products[i]));
				break;
			}
		}
	}

	memcpy(retData, inputData, sizeof(char)*20*50);

	return 0;

}

void printData(char kind[][20], int count)
{
	int i;

	printf("-------------------\n");
	printf("물품 종류\n");
	printf("-------------------\n");
	for(i=0; i<count; i++)
	{
		printf("%s \n", kind[i]);
	}
	printf("\n");
}
