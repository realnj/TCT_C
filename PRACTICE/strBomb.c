#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

/*
 * mirkovC4nizCC44
	C4
	->mirkovniz
 */
int main(void)
{
	char str[100]={0,};
	char str2[100]={0,};
	char tmp[100]={0,};
	int i=0;
	int len = 0;

	scanf("%s",str);
	scanf("%s",str2);
	len = strlen(str);

	for(i=0; i<len; i++)
	{
		if(memcmp(&str[i], &str2[0], strlen(str2))==0)
		{
			memcpy(&tmp[0], &str[0], i);

			len -=strlen(str2);
			memcpy(&tmp[i], &str[i+2], len-i);

			memset(str, 0x00, 100);
			memcpy(str, tmp, len);
			memset(tmp, 0x00, 100);

			i=0;
		}
	}

	printf("//str = %s\n", str);
}

