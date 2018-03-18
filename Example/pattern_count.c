#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

int patternCount(char *source, char *pattern, char type);


int main(int argc, char **argv)
{
	char buffer[1024] ={0,};
	char case_sensitive = argv[1][0]; // S :대소문자 구분, I : 대소문자 구분안함
	char *pattern = *(argv + 2);
	char *file_name = *(argv+3);
	int total_count = 0;

	FILE *fp = fopen(file_name, "r");
	if(fp == NULL)
	{
		printf("입력 파일 오픈 오류\n");
		return -1;
	}

	while(fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		total_count += patternCount(buffer, pattern, case_sensitive);
	}

	printf("%d", total_count);

	return 0;

}

int patternCount(char *source , char *pattern, char type)
{
	int count = 0;
	char *temp = NULL;

	if(type == 'I') // 대소문자 구분 안함
	{
		strupr(source);
		strupr(pattern);
	}

	while(source != NULL)
	{
		temp = strstr(source, pattern);
		if(temp != NULL)
		{
			temp += 1;
			source = temp;
			count ++;
		}
		source = temp;
	}
	return count;
}
