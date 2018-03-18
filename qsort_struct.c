#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

typedef struct
{
	char name[16];
	int price;
	int quantity;
}product;

void print_struct_array(product *array, int len);
int compare_func_des(const void *a, const void *b);
int compare_func_aes(const void*a, const void *b);
int compare_func_aes_str(const void *a, const void *b);
int compare_func_des_twotype(const void *a, const void*b);
int compare_func_aes_twotype(const void *a, const void*b);
int compare_func_aes_threetype(const void *a, const void *b);

int main(void)
{

	product p[] ={
			{"CUP", 29900, 100},
			{"CUP", 29900, 50},
			{"OLED TV", 2200000, 2},
			{"NOTEBOOK", 1300000, 39},
			{"SMARTPHONE", 590000, 80},
			{"PLAYSTATION", 14000, 43},
			{"COOKIE", 2990, 299},
			{"DESK", 2990, 500},
			{"COOKIE", 2990, 500},
			{"APPLE", 29900, 50},
			{"DOLL", 1300000, 39}
	};

	// ����ü�� ���� ���
	int structs_len = sizeof(p) / sizeof(product);

	// sort�ϱ� �� ����ü �迭�� ���� ���
	printf("SORT ��\n");
	print_struct_array(p, structs_len);

	// qsort�Լ��� ����ü �迭�� �ּҿ� ũ�� �׸��� �񱳿� ����� �Լ���
	// �ּҸ� ���ڷ� �Ѱܼ� ����
	qsort(p, structs_len, sizeof(product), compare_func_des);

	printf("���� sort ���(��������)\n");
	print_struct_array(p, structs_len);

	qsort(p, structs_len, sizeof(product), compare_func_aes);
	printf("���� sort ���(��������)\n");
	print_struct_array(p, structs_len);

	qsort(p, structs_len, sizeof(product), compare_func_des_twotype);
	printf("����, ���� sort ���(��������)\n");
	print_struct_array(p, structs_len);

	qsort(p, structs_len, sizeof(product), compare_func_aes_str);
	printf("��ǰ�� sort ���(��������)\n");
	print_struct_array(p, structs_len);

	qsort(p, structs_len, sizeof(product), compare_func_aes_threetype);
	printf("����, ����, ��ǰ�� sort ���(��������)\n");
	print_struct_array(p, structs_len);
}

/* ����ü �迭�� �ּҿ� ���̸� �޾Ƽ� ����ü�� ����ϴ� �Լ�*/
void print_struct_array(product *array, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("[%d] ��ǰ��:%s \t ����: %8d \t ����: %d\n",
				i, array[i].name, array[i].price, array[i].quantity);
	}
}

// �������� 3, 2, 1
int compare_func_des(const void *a, const void *b)
{
	product *left = (product *)a;
	product *right = (product *)b;

	if(left->price <right->price)
	{
		return 1;
	}
	else if(left->price > right->price)
	{
		return -1;
	}
	return 0;
}
// �������� 3, 2, 1 / CBA
int compare_func_des_twotype(const void *a, const void *b)
{
	product *left = (product *)a;
	product *right = (product *)b;

	if(left->price <right->price)
	{
		return 1;
	}
	else if(left->price > right->price)
	{
		return -1;
	}
	else
	{
		if(left->quantity < right->quantity)
		{
			return 1;
		}
		else if(left->quantity > right->quantity)
		{
			return -1;
		}
	}
}

//�������� 1,2,3 / ABC
int compare_func_aes(const void *a, const void *b)
{
	product *left = (product *)a;
	product *right = (product *)b;

	if(left->quantity > right->quantity)
	{
		return 1;
	}
	else if(left->quantity < right->quantity)
	{
		return -1;
	}
	return 0;
}

int compare_func_aes_twotype(const void *a, const void *b)
{
	product *left = (product *)a;
	product *right = (product *)b;

	if(left->price > right->price)
	{
		return 1;
	}
	else if(left->price < right->price)
	{
		return -1;
	}
	else
	{
		if(left->quantity > right->quantity)
		{
			return 1;
		}
		else if(left->quantity < right->quantity)
		{
			return -1;
		}
	}
}
// �������� abc  A�� B���� ũ�� 1��ȯ, B�� A���� ũ�� -1
int compare_func_aes_str(const void *a, const void *b)
{
	product *left = (product *)a;
	product *right = (product *)b;

    return strcmp( left->name , right->name );
}

int compare_func_aes_threetype(const void *a, const void *b)
{
	product *left = (product *)a;
	product *right = (product *)b;

	if(left->price > right->price)
	{
		return 1;
	}
	else if(left->price < right->price)
	{
		return -1;
	}
	else
	{
		if(left->quantity > right->quantity)
		{
			return 1;
		}
		else if(left->quantity < right->quantity)
		{
			return -1;
		}
		else
		{
			return strcmp( left->name , right->name );
		}
	}
}
