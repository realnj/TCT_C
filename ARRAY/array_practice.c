#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

#define MAX_SIZE 128

void loadData();
void printData();
void reversalPhoto(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width);
void zoomScale(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width);
void rotatePhoto(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width);
void rotateRightPhoto(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width);
void drawEdge(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width);
char inputPhotoAry[MAX_SIZE][MAX_SIZE];
char outputPhotoAry[MAX_SIZE][MAX_SIZE];
int rowNum =0, colNum=0; // 배열의 크기

int main(void)
{
	char returnPhotoAry[MAX_SIZE][MAX_SIZE];
	int tmp =0;

	loadData();

	// 원본 출력
	printf("-----(0) 원본 사진.=-----\n");
	printData(inputPhotoAry, rowNum, colNum);

	// 좌우 반전
	reversalPhoto(returnPhotoAry, inputPhotoAry, rowNum, colNum);
	memcpy(outputPhotoAry, returnPhotoAry, sizeof(outputPhotoAry));
	printf("-----(1) 좌우 반전된 사진.=-----\n");
	printData(outputPhotoAry, rowNum, colNum);
	memcpy(inputPhotoAry, outputPhotoAry, sizeof(inputPhotoAry));

	//2배 확대
	zoomScale(returnPhotoAry, inputPhotoAry, rowNum, colNum);
	memcpy(outputPhotoAry, returnPhotoAry, sizeof(outputPhotoAry));
	printf("-----(2) 2배 확대된 사진-----\n");
	rowNum *=2;
	colNum *=2;
	printData(outputPhotoAry, rowNum, colNum);
	memcpy(inputPhotoAry, outputPhotoAry, sizeof(inputPhotoAry));

	// 왼쪽 90도 회전
	rotatePhoto(returnPhotoAry, inputPhotoAry, rowNum, colNum);
	memcpy(outputPhotoAry, returnPhotoAry, sizeof(outputPhotoAry));
	printf("-----(3) 왼쪽으로 90도 회전된 사진-----\n");
	tmp = colNum;
	colNum = rowNum;
	rowNum = tmp;
	printData(outputPhotoAry, rowNum, colNum);
	memcpy(inputPhotoAry, outputPhotoAry, sizeof(inputPhotoAry));

	// 오른쪽 90도 회전
	rotateRightPhoto(returnPhotoAry, inputPhotoAry, rowNum, colNum);
	memcpy(outputPhotoAry, returnPhotoAry, sizeof(outputPhotoAry));
	printf("-----(4) 오른쪽으로 90도 회전된 사진-----\n");
	tmp = colNum;
	colNum = rowNum;
	rowNum = tmp;
	printData(outputPhotoAry, rowNum, colNum);
	memcpy(inputPhotoAry, outputPhotoAry, sizeof(inputPhotoAry));

	// 테두리가 추가된 사진
	drawEdge(returnPhotoAry, inputPhotoAry, rowNum, colNum);
	memcpy(outputPhotoAry, returnPhotoAry, sizeof(outputPhotoAry));
	printf("-----(5) 테두리가 추가된 사진-----\n");
	printData(outputPhotoAry, rowNum+2, colNum+2);

}

/* 2차원 배열을 좌우 반전시킨다.*/
void reversalPhoto(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width)
{
	int i,k;
	for(i=0; i<height; i++)
	{
		for(k=0; k<width; k++)
		{
			retAry[i][width-k-1] = photoAry[i][k];
		}
	}

}

/* 2차원 배열을 2배 확대 시킨다. */
void zoomScale(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width)
{
	int i,k;

	for(i=0; i<height*2; i++)
	{
		for(k=0; k<width*2; k++)
		{
			retAry[i][k] = photoAry[(int)i/2][(int)k/2];
		}
	}
}


/*2차원 배열을 왼쪽으로 90도 회전시킨다.*/

void rotatePhoto(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width)
{
	int i,k;

	for(i=0; i<height; i++)
	{
		for(k=0; k<width; k++)
		{
			retAry[width-k-1][i] = photoAry[i][k];
		}
	}
}
/* 2차원 배열을 오른쪽으로 90도 회전시킨다. */
void rotateRightPhoto(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width)
{
	int i,k;

	for(i=0; i<height; i++)
	{
		for(k=0; k<width; k++)
		{
			retAry[k][height-i-1] = photoAry[i][k];
		}
	}
}

void drawEdge(char retAry[][MAX_SIZE], char photoAry[][MAX_SIZE], int height, int width)
{
	int i,k;

	for(i=0; i<height+2; i++)
	{
		for(k=0; k<width+2; k++)
		{
			retAry[i][k] = '*';
		}
	}

	for(i=1; i<height+1; i++)
	{
		for(k=1; k<width+1; k++)
		{
			retAry[i][k] = photoAry[i-1][k-1];
		}
	}

}
void loadData()
{
	memset(inputPhotoAry, 0, sizeof(inputPhotoAry));

	rowNum = 4;
	colNum =2;

	char data[MAX_SIZE][MAX_SIZE] ={ {'C', 'D'},
															{'K', 'P'},
															{'A', 'R'},
															{'P', 'Q'}
	};

	memcpy(inputPhotoAry, data, sizeof(inputPhotoAry));
}

void printData(char photo[MAX_SIZE][MAX_SIZE], int x, int y)
{
	int i, k;
	for(i=0; i<x; i++)
	{
		for(k=0; k<y; k++)
		{
			printf("%c ", photo[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}
