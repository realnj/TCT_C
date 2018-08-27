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
		//�������� �и��� ���� �б�
		fscanf( fp_in, "%d %f %s\n", &nCount, &fRatio, strDesc );
		printf( "�������� �и� : %d %f %s\n", nCount, fRatio, strDesc );

		//,�� �и��� ���� �б�
		fscanf( fp_in, "%d, %f, %s\n", &nCount, &fRatio, strDesc );
		printf( ",�� �и� : %d, %f, %s\n", nCount, fRatio, strDesc );

		//������ �и��� ���� �б�
		fscanf( fp_in, "%d\t%f\t%s\n", &nCount, &fRatio, strDesc );
		printf( "������ �и� : %d\t%f\t%s\n", nCount, fRatio, strDesc );

		//���������� �б� - [%*]�� ����ϸ� ���� ���� �ʴ´�.
		fscanf( fp_in, "%*d %*f %s\n", strDesc );
		printf( "���������� �б� : %s\n", strDesc );
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
