#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
#define LEN 10
#define MAX_CNT 5
#define STR_LEN 50

void bubbleSortArr(int *list, const int n);
void bubbleSortStr(char sortedBooks[MAX_CNT][STR_LEN], char books[MAX_CNT][STR_LEN]);
void bubbleSortStr2(char *sortedBooks[MAX_CNT], char *books[MAX_CNT]);

void printArr(int *list, int n);
void printStrList(char books[MAX_CNT][STR_LEN]);
void printStrList2(char *books[MAX_CNT]);

int main(void)
{
	int array[10] = {3,6,4,8,9,1,2,5,7,10};

	char books[MAX_CNT][STR_LEN] ={
			"Deep Learning_2018",
			"Weapons of Math Destruction_2011",
			"Computer Systems_2018",
			"Bitcoin and Cryptocurrency Technologies_2016",
			"Code Complete_2017"
	};

	char *books2[] ={
			"Deep Learning_2018",
			"Weapons of Math Destruction_2011",
			"Computer Systems_2018",
			"Bitcoin and Cryptocurrency Technologies_2016",
			"Code Complete_2017"
	};

	char sortedBooks[MAX_CNT][STR_LEN];
	char *sortedBooks2[STR_LEN];


	printf("before bubble sort\n");
	bubbleSortArr(array, LEN);
	printf("after bubble sort\n");
	printArr(array, LEN);
	printf("======================\n");

	printf("before bubble sort\n");
	printStrList(books);
	printf("======================\n");
	bubbleSortStr(sortedBooks, books);
	printf("after bubble sort\n");
	printStrList(sortedBooks);
	printf("======================\n");

	printf("before bubble sort\n");
	bubbleSortStr2(sortedBooks2, books2);
	printf("after bubble sort\n");
	printStrList2(sortedBooks2);

	return 0;
}

void bubbleSortArr(int *list, const int n)
{
	int tmp=0;
	int i=0;
	int j=0;

	for(i =0; i<n-1; i++)
	{
		for(j=0; j<n-1-i; j++)
		{
			if(list[j] > list[j+1])
			{
				tmp = list[j];
				list[j] = list[j+1];
				list[j+1] = tmp;
			}
		}
	}
}

void bubbleSortStr(char sortedBooks[MAX_CNT][STR_LEN], char books[MAX_CNT][STR_LEN])
{
	int tmp=0;
	int i=0;
	int j=0;

	for(i =0; i<MAX_CNT; i++)
	{
		strcpy(sortedBooks[i], books[i]);
		printf("%s\n", sortedBooks[i]);
	}


	char swap[MAX_CNT][STR_LEN];

	for(i =0; i<MAX_CNT-1; i++)
	{
		for(j=0; j<MAX_CNT-1-i; j++)
		{
			if(strcmp(sortedBooks[j], sortedBooks[j+1]) > 0)
			{
				strcpy(swap, sortedBooks[j]);
				strcpy(sortedBooks[j], sortedBooks[j+1]);
				strcpy(sortedBooks[j+1], swap);
			}
		}
	}
}


void bubbleSortStr2(char *sortedBooks[STR_LEN], char *books[STR_LEN])
{
	int tmp=0;
	int i=0;
	int j=0;

	for(i =0; i<MAX_CNT; i++)
	{
		sortedBooks[i] = books[i];
		printf("%s\n", sortedBooks[i]);
	}

	char *swap;
	for(i =0; i<MAX_CNT-1; i++)
	{
		for(j=0; j<MAX_CNT-1-i; j++)
		{
			if(strcmp(sortedBooks[j], sortedBooks[j+1]) > 0)
			{
				swap = sortedBooks[j];
				sortedBooks[j] =  sortedBooks[j+1];
				sortedBooks[j+1] =  swap;
			}
		}
	}
}

void printArr(int *list, int n)
{
	int i;
	for(i=0; i<n; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
}

void printStrList(char books[MAX_CNT][STR_LEN])
{
	for(int i=0; i<MAX_CNT; i++)
	{
		printf("%d. %s\n", i+1, books[i]);
	}
}

void printStrList2(char *books[STR_LEN])
{
	for(int i=0; i<MAX_CNT; i++)
	{
		printf("%d. %s\n", i+1, books[i]);
	}
}
