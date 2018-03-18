#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

#define MAX_COUNT 10

void print_array_int(int *array, int len);
void print_array_char(char (*str)[20], int len);
int compare_des_int(const void *a, const void *b);
int compare_aes_int(const void*a, const void *b);
int compare_des_char(const void *a, const void*b);
int compare_aes_char(const void *a, const void*b);

int main(void)
{
	int arr[] = {4,3,1,7,5,9,8,2,6};
	int arr_size = sizeof(arr) / sizeof(int);
	char str[MAX_COUNT][20] = {"apple", "banana", "strawberry", "grape", "coffee",
			                       "cocoa", "melon", "milk", "mushroom", "butter"};

	// sort하기 전 구조체 배열의 내용 출력
	printf("SORT 전\n");
	print_array_int(arr, arr_size);

	qsort(arr, arr_size, sizeof(int), compare_des_int);

	printf("array sort(내림차순)\n");
	print_array_int(arr, arr_size);

	qsort(arr, arr_size, sizeof(int), compare_aes_int);
	printf("array sort(오름차순)\n");
	print_array_int(arr, arr_size);

	qsort(str, MAX_COUNT, sizeof(str[0]), compare_des_char);
	printf("string sort 결과(내림차순)\n");
	print_array_char(str, MAX_COUNT);

	qsort(str, MAX_COUNT, sizeof(str[0]), compare_aes_char);
	printf("string sort 결과(오름차순)\n");
	print_array_char(str, MAX_COUNT);
}

void print_array_int(int *array, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("array[%d] = %d\n", i, array[i]);
	}
}

void print_array_char(char (*str)[20], int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("str[%d] = %s\n", i, str[i]);
	}
}

// 내림차순 3, 2, 1
int compare_des_int(const void *a, const void *b)
{
	int left = *(int *)a;
	int right = *(int *)b;

	if( left  < right )
	{
		return 1;
	}
	else if( left > right )
	{
		return -1;
	}
	return 0;
}

//오름차순 1,2,3
int compare_aes_int(const void *a, const void *b)
{
	int left = *(int *)a;
	int right = *(int *)b;

	if( left  > right )
	{
		return 1;
	}
	else if( left < right )
	{
		return -1;
	}
	return 0;
}

// 내림차순 3, 2, 1
int compare_des_char(const void *a, const void *b)
{
    return strcmp( (char*)a , (char*)b );
}

// 내림차순 3, 2, 1
int compare_aes_char(const void *a, const void *b)
{
    return strcmp( (char*)b , (char*)a );
}

///////////////////////
//#define MAX 5
//int compare(const void *x,const void *y); // 비교함수 strcmp 를 사용
//
//
//int main()
//{
// char *word[MAX]; // 문자열 저장 포인터
// char buffer[20]; // 임지저장영역
// int i; //반복제어변수
//
// for ( i = 0 ; i < MAX ; i++ )
// {
//  printf("문자열 입력 : ");
//  scanf("%s", buffer);
//  word[i] = (char *)malloc(strlen(buffer) + 1);
//  strcpy(word[i] , buffer);
// }
//
// printf("sizeof(word[0] = %d\n", sizeof(word[0]));
// qsort(word,MAX,sizeof(word[0]),compare); // 정렬
////qsort(저장배열포인터,최대크기,바이트수,비교함수);
// for ( i = 0 ; i < MAX ; i++ )
// {
//  printf("%s\n",word[i]);
// }
//
// return 0;
//}
//
//int compare(const void *x,const void *y)
//{
// return (strcmp(*(char **)x , *(char **)y));
//}


