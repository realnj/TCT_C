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
	 char *word[MAX]; // ���ڿ� ���� ������
	 char buffer[20]; // �������念��
	 int i; //�ݺ������

	 for ( i = 0 ; i < MAX ; i++ )
	 {
		  printf("���ڿ� �Է� : ");
		  scanf("%s", buffer);
		  word[i] = (char *)malloc(strlen(buffer) + 1);
		  strcpy(word[i] , buffer);
	 }

	//qsort(����迭������,�ִ�ũ��,����Ʈ��,���Լ�);
	 qsort(word,MAX,sizeof(word[0]),compare_aes_malloc); // ����

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



