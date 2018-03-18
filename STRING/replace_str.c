#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

int replaceStr(char *str, char *pattern, char *change);

int main(void)
{
	char str[100]={0,};
	char pattern[100] ={0,};
	char change[100]={0,};

	scanf("%s", str);
	scanf("%s", pattern);
	scanf("%s", change);

	printf("org = %s\n",str);
	replaceStr(str, pattern, change);
	printf("change = %s\n",str);
}


int replaceStr(char *str, char *pattern, char *change)
{
	int i=0;
	int j=0;
	int len =0;
	char result[100]={0,};

	len = strlen(str);
	for(i=0; i<len; i++)
	{
		if(memcmp(&str[i], pattern, strlen(pattern))==0)
		{
			memcpy(&result[j], change, strlen(change));
			j += strlen(change);
			i += strlen(pattern)-1;
//			printf("i= %d j=%d\n", i, j);
		}
		else
		{
			result[j] = str[i];
			j++;
		}
	}
//	printf("result = %s\n", result);
	memset(str, 0x00, 100);
	memcpy(str, result, strlen(result));
}
