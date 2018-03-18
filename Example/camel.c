#include<stdio.h>
#include<string.h>
#include <stdlib.h>


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

int main(int argc, char **argv)
{
	char *temp = argv[1];

	int len = strlen(temp);

	char *str= temp;

	for(int i=0; i<len; i++)
	{
		if(str != '\0')
		{
			if(*str == '_')
			{
				memmove(str, str+1, len-i);
				*str = toupper(*str);
			}
			str++;
		}
	}

	printf("%s\n", temp);
}
