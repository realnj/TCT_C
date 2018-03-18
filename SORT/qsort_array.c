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

	// sort�ϱ� �� ����ü �迭�� ���� ���
	printf("SORT ��\n");
	print_array_int(arr, arr_size);

	qsort(arr, arr_size, sizeof(int), compare_des_int);

	printf("array sort(��������)\n");
	print_array_int(arr, arr_size);

	qsort(arr, arr_size, sizeof(int), compare_aes_int);
	printf("array sort(��������)\n");
	print_array_int(arr, arr_size);

	qsort(str, MAX_COUNT, sizeof(str[0]), compare_des_char);
	printf("string sort ���(��������)\n");
	print_array_char(str, MAX_COUNT);

	qsort(str, MAX_COUNT, sizeof(str[0]), compare_aes_char);
	printf("string sort ���(��������)\n");
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

// �������� 3, 2, 1
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

//�������� 1,2,3
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

// �������� 3, 2, 1
int compare_des_char(const void *a, const void *b)
{
    return strcmp( (char*)a , (char*)b );
}

// �������� 3, 2, 1
int compare_aes_char(const void *a, const void *b)
{
    return strcmp( (char*)b , (char*)a );
}

///////////////////////
//#define MAX 5
//int compare(const void *x,const void *y); // ���Լ� strcmp �� ���
//
//
//int main()
//{
// char *word[MAX]; // ���ڿ� ���� ������
// char buffer[20]; // �������念��
// int i; //�ݺ������
//
// for ( i = 0 ; i < MAX ; i++ )
// {
//  printf("���ڿ� �Է� : ");
//  scanf("%s", buffer);
//  word[i] = (char *)malloc(strlen(buffer) + 1);
//  strcpy(word[i] , buffer);
// }
//
// printf("sizeof(word[0] = %d\n", sizeof(word[0]));
// qsort(word,MAX,sizeof(word[0]),compare); // ����
////qsort(����迭������,�ִ�ũ��,����Ʈ��,���Լ�);
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


