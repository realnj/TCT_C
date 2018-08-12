#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
int cnt;
char input[20][20];

int makeNormalData(char *result[15]);
void printData(char *kind[20], int count);
int organizeProductCode( char *product[10], char *input[15], char *output[15]);

int main(void)
{
	char *product[6];
	char *lowerStr[15]={0,};
	char *outStr[15]={0,};
	int i=0;

	loadData(product);

	makeNormalData(lowerStr);
	printData(lowerStr, 15);

	organizeProductCode(product, lowerStr, outStr);
	printData(outStr, 15);

}

int organizeProductCode( char *product[6], char *lowerStr[15], char *output[15])
{
	int i=0;
	int j=0;
	int m=0;
	int n=0;
	char **arr;
	int len =0;
	char checkArr[10]={0,};

	arr= (char**)malloc(sizeof(char*)*15);

	for(i=0; i<15; i++)
	{
		arr[i]= (char*)malloc(sizeof(char)*20);
		memset(arr[i], 0x00, 20);
	}

	for(i=0; i<15; i++)
	{
		arr[i] = lowerStr[i];
	}

	for(i=0; i<15; i++)
	{
		len =0;
		memset(checkArr, 0x00, 10);
		for(j=0; j<strlen(arr[i]); j++)
		{
			for(m=0; m<6; m++)
			{
				for(n=0; n<strlen(product[m]); n++)
				{
					if(strlen(arr[i]) != strlen(product[m]))
					{
						break;
					}
					if(arr[i][j] == product[m][n] && checkArr[n] ==0)
					{
						checkArr[n] = 1;
						len++;
						break;
					}
				}

				if(len == strlen(arr[i]))
				{
					strcpy(arr[i], product[m]);
					len = 0;
				}
			}
		}
	}

	for(i=0; i<15; i++)
	{
		output[i] = arr[i];
	}
}

int makeNormalData(char *result[15])
{
	char str[20][20]={0,};
	char **arr;
	int i=0;
	int j=0;
	int m=0;

	arr= (char**)malloc(sizeof(char*)*15);

	for(i=0; i<15; i++)
	{
		arr[i]= (char*)malloc(sizeof(char)*20);
		memset(arr[i], 0x00, 20);
	}

	for(i=0; i<15; i++)
	{
		m=0;
		for(j=0; j<strlen(input[i]); j++)
		{
			if(input[i][j] >='a' && input[i][j]<='z')
			{
				arr[i][m]= input[i][j];
				m++;
			}
			else if(input[i][j] >= 'A' && input[i][j]<='Z')
			{
				arr[i][m]= tolower(input[i][j]);
				//arr[i][m] += 'a'-'A';
				m++;
			}
		}
	}

	for(i=0; i<15; i++)
	{
		result[i] = arr[i];
	}

}

int loadData(char *product[6])
{
	char *arr[6]={"coffee", "water", "milk", "paper", "rice", "ramen"};
	char data[15][20] ={"coffee", "eeFFCo", "amenr", "Ra Men", "CO FFE E",
			"coFfee", "c#off$ee", "cOe f%%&f*e", "RiCE", "*Ri&c@e",
			"water", "FFCOEE", "WATER", "TERAW", "*tW$a ER#"
	};

	int i, j=0;

	for(i=0; i<6; i++)
	{
		product[i] = arr[i];
	}

	memset(input, 0, sizeof(input));
	memcpy(input, data, sizeof(data));

}

void printData(char *kind[15], int count)
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

