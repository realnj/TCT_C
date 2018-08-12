#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
int replaceZeroLine(int *arr, int *input);
int makeArray(int *input, int size, int (*array)[5]);
int printArray(int arrSize, int (*array)[5]);

int main(void)
{
	int input[30]={1,2,3,5,2,
			 	 	 	 2,2,6,8,9,
						 9,2,6,6,6,
						 7,5,6,4,4,
						 4,1,1,1,3,
						 3,3,4
	};
	int arr[30]={0,};
	int array[5][5]={0,};
	int arrSize = 5;
	int i=0;
	int j=0;

	replaceZeroLine(arr, input);

	makeArray(input, arrSize, array);
	printArray(arrSize, array);
	replaceZeroArray(arrSize, array);
	printArray(arrSize, array);
}
int printArray(int arrSize, int (*array)[5])
{
	int i, j=0;

	printf("=============\n");
	for(i=0; i<arrSize; i++)
	{
		for(j=0; j<arrSize; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
}
int replaceZeroArray(int arrSize, int (*array)[5])
{
	int i=0;
	int j=0;
	int m=0;
	int n=0;
	int arr[5][5]={0,};

	for(i=0; i<arrSize; i++)
	{
		for(j=0; j<arrSize; j++)
		{
			arr[i][j] = array[i][j];
		}
	}

	for(i=0; i<arrSize; i++)
	{
		for(j=0; j<arrSize; j++)
		{
			// 오른쪽으로
			if(j+2<arrSize)
			{
				if(array[i][j] == array[i][j+1] && array[i][j] == array[i][j+2])
				{
					arr[i][j] = 0;
					arr[i][j+1]=0;
					arr[i][j+2]=0;
				}

			}

			if(i+2 <arrSize)
			{
				if(array[i][j] == array[i+1][j] && array[i][j] == array[i+2][j])
				{
					arr[i][j] = 0;
					arr[i+1][j]=0;
					arr[i+2][j]=0;
				}
			}

		}
	}

	for(i=0; i<arrSize; i++)
	{
		for(j=0; j<arrSize; j++)
		{
			array[i][j] = arr[i][j];
		}
	}
}

int makeArray(int *input, int size, int (*array)[5])
{
	int i=0;
	int j=0;
	int m=0;

	for(i=0; i<size; i++)
	{
		for(j=0; j<5; j++)
		{
			array[i][j] = input[m];
			m++;
		}
	}
}

int replaceZeroLine(int *arr, int *input)
{
	int i=0;
	int cnt =1;
	int j=0;

	for(i=0; i<28; i++)
	{
		arr[i] = input[i];
		printf("%d ", arr[i]);
	}
	printf("\n");

	for(i=1; i<28; i++)
	{
		if(arr[i-1] == arr[i])
		{
			cnt++;
		}
		else
		{
			if(cnt >=3)
			{
				j=i-1;
				while(cnt>0){
					arr[j] = 0;
					j--;
					cnt--;
				}
			}
			cnt =1;
		}
	}
}
