#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

#define ARRAY_LENGTH 5
void loadArray();
int getMaxSum(int (*numData)[ARRAY_LENGTH]);
void replaceArray(int retData[][ARRAY_LENGTH], int (*arr)[ARRAY_LENGTH]);
int numData[ARRAY_LENGTH][ARRAY_LENGTH];

int main(void)
{
	int returnData[ARRAY_LENGTH][ARRAY_LENGTH]={0,};
	int maxSum =0;

	loadArray();
	printf("초기 배열\n");
	printData(ARRAY_LENGTH, numData);

	replaceArray(returnData, numData);
	memcpy(numData, returnData, sizeof(numData));
	printf("치환 후 배열\n");
	printData(ARRAY_LENGTH, numData);

	maxSum= getMaxSum(numData);

	printf("maxSum = %d\n", maxSum);

}

int getMaxSum(int (*numData)[ARRAY_LENGTH])
{
	int i, j=0;
	int m, n=0;
	int sum=0;
	int maxSum=0;

	for(i=0; i<ARRAY_LENGTH-1; i++)
	{
		for(j=0; j<ARRAY_LENGTH-1; j++)
		{
			sum=0;
			for(m=i; m<2+i; m++)
			{
				for(n=j; n<2+j; n++)
				{
					sum+= numData[m][n];
				}
			}

			if(maxSum<sum)
			{
				maxSum = sum;
			}
		}
	}


	return maxSum;
}

void replaceArray(int retData[][ARRAY_LENGTH], int (*arr)[ARRAY_LENGTH])
{
	int i, j=0;

	for(i=0; i<ARRAY_LENGTH; i++)
	{
		for(j=0; j<ARRAY_LENGTH; j++)
		{
			if(arr[i][j] < 0)
			{
				retData[i][j] = 0;
			}
			else if(arr[i][j]> 100)
			{
				retData[i][j] = arr[i][j]%100;
			}
			else
			{
				retData[i][j] = arr[i][j];
			}
		}
	}
}

void loadArray()
{
	int array[5][5] ={ {5, -7, -5, 100, 73},
								{36, 69, 90, 233, 7},
								{49, 85, 556, 34, 43},
								{124, -59, -86, 54, 52},
								{233, 43, 8, 78, 0}
	};


	memcpy(numData, array, sizeof(array));

}

void printData(int dataLen, int data[][ARRAY_LENGTH])
{
	int i, j=0;
	for(i=0; i<dataLen; i++)
	{
		for(j=0; j<dataLen; j++)
		{
			printf("%5d", data[i][j]);
		}
		printf("\n");
	}
	printf("-------------------------------------\n");
}
