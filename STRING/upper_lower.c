#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

void toUpper(char *str)
{
	while(*str)
	{
		*str = toupper(*str);
		str++;
	}
}

void toLower(char *str)
{
	while(*str)
	{
		*str = tolower(*str);
		str++;
	}
}

int main(void)
{
	char str[10] = "abcdef";
	char str2[10]="apple";

	toUpper(str);
	printf("%s\n", str);
	toLower(str);
	printf("%s\n", str);

	strupr(str2);
	printf("%s\n", str2);
	strlwr(str2);
	printf("%s\n", str2);

}
