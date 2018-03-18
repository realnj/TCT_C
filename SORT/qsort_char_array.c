#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

#define MAX_COUNT 10

void print_array_char(char (*str)[20], int len);
int compare_des_char(const void *a, const void*b);
int compare_aes_char(const void *a, const void*b);

int main(void)
{
	char str[MAX_COUNT][20] = {"apple", "banana", "strawberry", "grape", "coffee",
			                       "cocoa", "melon", "milk", "mushroom", "butter"};


	qsort(str, MAX_COUNT, sizeof(str[0]), compare_des_char);
	printf("string sort 결과(내림차순)\n");
	print_array_char(str, MAX_COUNT);

	qsort(str, MAX_COUNT, sizeof(str[0]), compare_aes_char);
	printf("string sort 결과(오름차순)\n");
	print_array_char(str, MAX_COUNT);
}

// 내림차순 cba
int compare_des_char(const void *a, const void *b)
{
    return strcmp( (char*)b , (char*)a );
}

// 오름차순 abc
int compare_aes_char(const void *a, const void *b)
{
    return strcmp( (char*)a , (char*)b );
}


void print_array_char(char (*str)[20], int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("str[%d] = %s\n", i, str[i]);
	}
}

