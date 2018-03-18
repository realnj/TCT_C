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

	// sort�ϱ� �� ����ü �迭�� ���� ���
	printf("SORT ��\n");
	print_array_int(arr, arr_size);

	qsort(arr, arr_size, sizeof(int), compare_des_int);
	printf("int array sort(��������)\n");
	print_array_int(arr, arr_size);

	qsort(arr, arr_size, sizeof(int), compare_aes_int);
	printf("int array sort(��������)\n");
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
