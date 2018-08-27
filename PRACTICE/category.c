#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_SIZE 20


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

char inputData[MAX_SIZE][MAX_SIZE];
int rowNum =0;

int countCategory(char inputData[MAX_SIZE][MAX_SIZE], int inputCount, char category);
void loadData();

int main(int argc, char *argv[])
{
	int count =0;

	loadData();
	count = countCategory(inputData, rowNum, 'L');

	printf("count = %d\n", count);
	return 0;
}
int countCategory(char inputData[MAX_SIZE][MAX_SIZE], int inputCount, char category)
{
	int numberOfCategory =0;
	int i=0;
	int j=0;
	char data[20]={0,};
	int idx =0;
	int size =0;
	for(i=0; i<inputCount; i++)
	{
		if(inputData[i][1]== category)
		{
			data[idx] = inputData[i][0];
			size++;
			break;
		}
	}

	while(idx<size)
	{
		for(i=0; i<inputCount; i++)
		{
			if(data[idx] == inputData[i][0])
			{
				for(j=0; j<size; j++)
				{
					if(data[j] == inputData[i][1])
					{
						break;
					}
				}

				if(j==size)
				{
					data[size] = inputData[i][1];
					printf("data[%d] = %c\n", size, data[size]);
					size++;
				}
			}
		}
		idx++;
	}

	numberOfCategory = size-1;
	return numberOfCategory;
}
void loadData()
{
	memset(inputData, 0x00, sizeof(inputData));

	rowNum = 15;
	char data[MAX_SIZE][MAX_SIZE] = {{'M', 'B'},
															 {'M', 'C'},
															 {'M', 'F'},
															 {'B', 'A'},
															 {'B', 'H'},
															 {'C', 'X'},
															 {'C', 'Y'},
															 {'F', 'L'},
															 {'F', 'T'},
															 {'A', 'K'},
															 {'H', 'G'},
															 {'X', 'O'},
															 {'L', 'S'},
															 {'T', 'U'},
															 {'T', 'W'},
	};

	memcpy(inputData, data, sizeof(data));
}
