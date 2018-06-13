#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	 readFile();
	 writeFile();
}

int readFile()
{
	FILE *fp_in;
	char buf_in[255] ={0,};

	fp_in = fopen("itemlist.txt", "r");

	if(fp_in==NULL)
	{
		perror("file open error 1: ");
		exit(0);
	}

	while(fgets(buf_in, 255, fp_in) != NULL)
	{
	//	printf("[%d]%s(%02x)", strlen(buf_in), buf_in, buf_in[strlen(buf_in)]);
		char *type = strtok(buf_in, "#\r\n");
		char *dtime = strtok(NULL, "#\r\n");
		char *code = strtok(NULL, "#\r\n");

	//	printf("\n");

//		printf("[(%d)%s] [(%d)%s] [(%d)%s]\n",
//				strlen(dtime), dtime,
//				strlen(type),type,
//				strlen(code), code);
	}

	fclose(fp_in);

	return 0;
}

int writeFile()
{
	FILE *fp_out;

	fp_out = fopen("OUTPUT.TXT", "a+");

	if(fp_out==NULL)
	{
		perror("file open error 1: ");
		exit(0);
	}

	for(int i=0; i<10; i++)
	{
		fprintf(fp_out, "%02d#%02d\n", i, 10-i);
	}

	fclose(fp_out);

	return 0;
}
