#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

void print_array_int(int *array, int len);
int compare_des_int(const void *a, const void *b);
int compare_aes_int(const void*a, const void *b);

int main(void)
{
	int arr[] = {4,3,1,7,5,9,8,2,6};
	int arr_size = sizeof(arr) / sizeof(int);

	// sort하기 전 구조체 배열의 내용 출력
	printf("SORT 전\n");
	print_array_int(arr, arr_size);

	qsort(arr, arr_size, sizeof(int), compare_des_int);
	printf("int array sort(내림차순)\n");
	print_array_int(arr, arr_size);

	qsort(arr, arr_size, sizeof(int), compare_aes_int);
	printf("int array sort(오름차순)\n");
	print_array_int(arr, arr_size);

}

void print_array_int(int *array, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("array[%d] = %d\n", i, array[i]);
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
