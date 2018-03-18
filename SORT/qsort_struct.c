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

	// 구조체의 길이 계산
	int structs_len = sizeof(p) / sizeof(product);

	// sort하기 전 구조체 배열의 내용 출력
	printf("SORT 전\n");
	print_struct_array(p, structs_len);

	// qsort함수에 구조체 배열의 주소와 크기 그리고 비교에 사용할 함수의
	// 주소를 인자로 넘겨서 정렬
	qsort(p, structs_len, sizeof(product), compare_func_des);

	printf("가격 sort 결과(내림차순)\n");
	print_struct_array(p, structs_len);

	qsort(p, structs_len, sizeof(product), compare_func_aes);
	printf("수량 sort 결과(오름차순)\n");
	print_struct_array(p, structs_len);

	qsort(p, structs_len, sizeof(product), compare_func_des_twotype);
	printf("가격, 수량 sort 결과(내림차순)\n");
	print_struct_array(p, structs_len);

	qsort(p, structs_len, sizeof(product), compare_func_aes_str);
	printf("상품명 sort 결과(오름차순)\n");
	print_struct_array(p, structs_len);

	qsort(p, structs_len, sizeof(product), compare_func_aes_threetype);
	printf("가격, 수량, 상품명 sort 결과(오름차순)\n");
	print_struct_array(p, structs_len);
}

/* 구조체 배열의 주소와 길이를 받아서 구조체를 출력하는 함수*/
void print_struct_array(product *array, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("[%d] 제품명:%s \t 가격: %8d \t 수량: %d\n",
				i, array[i].name, array[i].price, array[i].quantity);
	}
}

// 내림차순 3, 2, 1
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
// 내림차순 3, 2, 1 / CBA
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

//오름차순 1,2,3 / ABC
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
// 오름차순 abc  A가 B보다 크면 1반환, B가 A보다 크면 -1
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
