#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

typedef struct suffix
{
	char str[20];
	int num;
}SUFFIX;

SUFFIX stSuffix[20];

int compare_func_aes(const void *a, const void *b);
void print_struct_array(SUFFIX *array, int len);

int main(void)
{
	char str[20]={0,};
	char arr[20][20]={0,};
	char cmpStr[20]={0,};
	int i, j=0;
	int len = 0;
	int cmpStrLen=0;
	int same[20]={0,};
	scanf("%s", str);
	len = strlen(str);

	for(i=0; i<len; i++)
	{
		memcpy(stSuffix[i].str, &str[i], len-i);
		stSuffix[i].num = i+1;
	}

	qsort(stSuffix, len, sizeof(SUFFIX), compare_func_aes);

	print_struct_array(stSuffix, len);

	for(i=0; i<len; i++)
	{
		int strLen = strlen(stSuffix[i].str);
		if(i==0)
		{
			memcpy(cmpStr, stSuffix[i].str, strLen);
			cmpStrLen = strLen;
			printf("[x] ");
			continue;
		}
		for(j=0; j<cmpStrLen; j++)
		{
			if(stSuffix[i].str[j] == cmpStr[j])
			{
				same[i] +=1;
			}
			else
			{
				break;
			}
		}
		cmpStrLen = strLen;
		memset(cmpStr, 0x00, 20);
		memcpy(cmpStr, stSuffix[i].str, strLen);

		printf("[%d] ",same[i]);

	}

//	[x,1,3,0,0,2]
}

int compare_func_aes(const void *a, const void *b)
{
	SUFFIX *left = (SUFFIX *)a;
	SUFFIX *right = (SUFFIX *)b;

    return strcmp( left->str , right->str );
}

/* 구조체 배열의 주소와 길이를 받아서 구조체를 출력하는 함수*/
void print_struct_array(SUFFIX *array, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("[%d] ", array[i].num);
	}
	printf("\n");
}
