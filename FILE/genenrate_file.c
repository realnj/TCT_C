#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

FILE* file;

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

int validCheck(char* input);

void main(int ac, char** args)
{

	pthread_t thread;
	char typeList[7][3]={"aaa","bbb","ccc","ddd","eee","fff","ggg"};
	file = fopen("generatedFile.txt","w");

	if(file == NULL)
		return;

	if(ac!= 3 || !validCheck(args[1])|| !validCheck(args[2]))
	{
		printf("usage: generateFile.exe [count] [time gap(msec)]\nexample: generateFile.exe 100 1000\n");
		return;
	}

	int total_count = atoi(args[1]);
	int genertate_count=0;
	int timeGap = atoi(args[2]);


	while(genertate_count<total_count)
	{
		fprintf(file,"%.3s#merong%d\n",typeList[(genertate_count%7)],genertate_count);

		fsync(file);
		fflush(file);
		genertate_count++;
		usleep(timeGap*1000);

		printf("%d\n",genertate_count);
	}

	fprintf(file,"%c\n",'q');


	fclose(file);

}

int validCheck(char* input)
{
	for(int i=0; i<strlen(input);i++)
	{
		if(input[i]<'0'|| input[i]>'9')
			return 0;
	}
	return 1;
}

