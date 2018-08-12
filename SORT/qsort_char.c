#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

int compare_aes_char(const void *a, const void *b);
int compare_des_char(const void *a, const void *b);


int main(void)
{
	   char arrA[5][10] ={"feecaa", "likm", "iefrnd", "good"};
	   char arrB[5][10] ={"caffee", "milk", "friend", "dog"};
	   int i=0;

	   for(i=0; i<4; i++)
	   {
		   qsort(arrA[i], strlen(arrA[i]), sizeof(char), compare_aes_char);

		   qsort(arrB[i], strlen(arrB[i]), sizeof(char), compare_des_char);
	   }

	   for(i=0; i<4; i++)
	   {
		   printf("arrA[%d] =%s\n", i, arrA[i]);
	   }
	   printf("=======================\n");
	   for(i=0; i<4; i++)
	   {
		   printf("arrB[%d] =%s\n", i, arrB[i]);
	   }
}

int compare_des_char(const void *a, const void *b)
{
	char left = *(char*)a;
	char right = *(char*)b;

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

int compare_aes_char(const void *a, const void *b)
{
	char left = *(char*)a;
	char right = *(char*)b;

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
