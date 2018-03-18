#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

int replace(char *str, char source, char change);

//int main(int argc, char **argv)
int main(void)
{
//	char *temp = strdup(argv[1]);
	char temp[20]={0,};
	scanf("%s", temp);

	replace(temp, ',',' ');
	replace(temp, '.', ',');

	printf("%s", temp);

//	free(temp);
}

int replace(char *str, char source, char change)
{
	int len = strlen(str);

	for(int i=0; i<len; i++)
	{
		if(str[i] == source)
		{
			str[i] = change;
		}
	}
	return 0;
}
