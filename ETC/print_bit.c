#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//AHDFG, ADFGCDFFFFFG, ABAEFGCCDFEFFFFFG
//AHDFGA, DFGAH, ABABCC
void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}
/*
1000			 : 0000	0000	0000	0000	0000	0011	1110	1000
1234.56     : 0100	0100	1001	1010	0101	0001	1110	1100
-1              :1111	1111	1111	1111	1111	1111	1111	1111
-1.999999  :1011 1111	1111	1111	1111	1111	1111	1000

*/
void bit_prn(int n);
int main(int argc, char*argv[])
{
	float fNum;
	int nNum;
	char num[4]={0,};
	char *result;
	int i, j=0;

	nNum = -1;
	fNum = 1234.56f;

	memcpy(num, (char*)&nNum, 4);
	result = (char *)&fNum;

	for(i=3; i>=0; i--)
	{
		for(j=7; j>=0; j--)
		{
			printf("%d", (num[i]>>j)&0x01);

			if(j==4)
			{
				printf("\t");
			}
		}
		printf("\t");
	}

	printf("\n");

	for(i=3; i>=0; i--)
	{
		for(j=7; j>=0; j--)
		{
			printf("%d", (result[i]>>j)&0x01);

			if(j==4)
			{
				printf("\t");
			}
		}
		printf("\t");
	}

	bit_prn(nNum);
	printf(" : %d\n", nNum);
	bit_prn(*((int*)&fNum));
	printf(" : %f\n", fNum);

}

void bit_prn(int n) {

	for(int i=31; i>=0; i--)
	{
		printf("%d", ((n&(1<<i))==0)? 0:1);
		if(i !=0){
			printf("%s", ((i%4) ==0)? " ":"");
		}
	}
}
