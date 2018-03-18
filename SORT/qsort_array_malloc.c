#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
#define MAX 5
int compare_aes_malloc(const void *a, const void *b);

int main(void)
{
	 char *word[MAX]; // 문자열 저장 포인터
	 char buffer[20]; // 임지저장영역
	 int i; //반복제어변수

	 for ( i = 0 ; i < MAX ; i++ )
	 {
		  printf("문자열 입력 : ");
		  scanf("%s", buffer);
		  word[i] = (char *)malloc(strlen(buffer) + 1);
		  strcpy(word[i] , buffer);
	 }

	//qsort(저장배열포인터,최대크기,바이트수,비교함수);
	 qsort(word,MAX,sizeof(word[0]),compare_aes_malloc); // 정렬

	 for ( i = 0 ; i < MAX ; i++ )
	 {
		 printf("%s\n",word[i]);
	 }

	 return 0;
}

int compare_aes_malloc(const void *x,const void *y)
{
	return (strcmp(*(char **)x , *(char **)y));
}



