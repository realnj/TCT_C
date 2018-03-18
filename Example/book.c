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

void bubbleSortStr(char sortedBooks[MAX_CNT][STR_LEN], char books[MAX_CNT][STR_LEN]);
void printStrList(char books[MAX_CNT][STR_LEN]);
void printExtractList(char books[MAX_CNT][STR_LEN]);

int main(void)
{
	char books[MAX_CNT][STR_LEN] ={
			"Deep Learning_2018",
			"Weapons of Math Destruction_2011",
			"Computer Systems_2018",
			"Bitcoin and Cryptocurrency Technologies_2016",
			"Code Complete_2017"
	};

	char sortedBooks[MAX_CNT][STR_LEN];
	char extractedBooks[MAX_CNT][STR_LEN];

	int period = 2013;

	printf("before bubble sort\n");
	printStrList(books);
	printf("======================\n");
	bubbleSortStr(sortedBooks, books);
	printf("after bubble sort\n");
	printStrList(sortedBooks);
	printf("======================\n");

	extractLatestBook(extractedBooks, sortedBooks, period);
	printExtractList(extractedBooks);
	return 0;
}

void bubbleSortStr(char sortedBooks[MAX_CNT][STR_LEN], char books[MAX_CNT][STR_LEN])
{
	int tmp=0;
	int i=0;
	int j=0;

	for(i =0; i<MAX_CNT; i++)
	{
		strcpy(sortedBooks[i], books[i]);
//		printf("%s\n", sortedBooks[i]);
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

void extractLatestBook(char extractedBooks[MAX_CNT][STR_LEN], char sortedBooks[MAX_CNT][STR_LEN], int period)
{
	for(int i=0; i<MAX_CNT; i++)
	{
		strcpy(extractedBooks[i], "");
	}
	int extractedBookNumber =0;

	for(int i=0; i<MAX_CNT; i++)
	{
		char *ptr = strstr(sortedBooks[i], "_");
		int convertYear = atoi(ptr+1);
		if (convertYear > period)
		{
			strcpy(extractedBooks[extractedBookNumber], sortedBooks[i]);
			extractedBookNumber++;
		}
	}
}
void printStrList(char books[MAX_CNT][STR_LEN])
{
	for(int i=0; i<MAX_CNT; i++)
	{
		printf("%d. %s\n", i+1, books[i]);
	}
}
void printExtractList(char books[MAX_CNT][STR_LEN])
{
	for(int i=0; i<MAX_CNT; i++)
	{
		if(books[i][0])
		{
			printf("%d. %s\n", i+1, books[i]);
		}
	}
}
