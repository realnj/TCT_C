#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	 char pathBuf[50]={0,};
	 char *str ="ABCDEFGHIJ";

	 readFile();

	 sprintf(pathBuf, "./result.txt");
	 saveFile(pathBuf, str, 10);
}

int readFile()
{
	FILE *fp_in;
	char buf[10] ={0,};
	int nCount=0;
	float fRatio;
	char strDesc[255];

	fp_in = fopen("itemlist.txt", "r");

	if(fp_in==NULL)
	{
		perror("file open error 1: ");
		exit(0);
	}

	while(!feof(fp_in))
	{
		fscanf(fp_in, "%s %d", buf, &nCount);
		//공백으로 분리된 파일 읽기
		fscanf( fp_in, "%d %f %s\n", &nCount, &fRatio, strDesc );
		printf( "공백으로 분리 : %d %f %s\n", nCount, fRatio, strDesc );

		//,로 분리된 파일 읽기
		fscanf( fp_in, "%d, %f, %s\n", &nCount, &fRatio, strDesc );
		printf( ",로 분리 : %d, %f, %s\n", nCount, fRatio, strDesc );

		//탭으로 분리된 파일 읽기
		fscanf( fp_in, "%d\t%f\t%s\n", &nCount, &fRatio, strDesc );
		printf( "탭으로 분리 : %d\t%f\t%s\n", nCount, fRatio, strDesc );

		//선별적으로 읽기 - [%*]을 사용하면 값을 읽지 않는다.
		fscanf( fp_in, "%*d %*f %s\n", strDesc );
		printf( "선별적으로 읽기 : %s\n", strDesc );
	}

	fclose(fp_in);

	return 0;
}

void saveFile(char *szFullPath, char buf, int nLen)
{
	FILE *fp;
	fp = fopen(szFullPath, "ab");
	if(!fp)
	{
		return;
	}
	fwrite(buf, 1, nLen, fp);
	fclose(fp);
}
