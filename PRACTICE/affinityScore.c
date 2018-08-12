#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

int crossAssign(char *nameOne, char *nameTwo, int *num);

int main(void)
{
	char nameOne[10] ={0,};
	char nameTwo[10] ={0,};
	int num[20]={0,};
	int len1 =0;
	int len2 =0;
	int len = 0;
	int result =0;

	scanf("%s", nameOne); // LEE
	scanf("%s", nameTwo);  // KIM

	len1 = strlen(nameOne);
	len2 = strlen(nameTwo);

	makeSameLength(nameOne, nameTwo);

	crossAssign(nameOne, nameTwo, num);

	len = strlen(nameOne)*2;

	result = affinityScore(num, len);
	printf("result =%d%\n", result);
}
int affinityScore(int *num, int len)
{
	int i=0;
	int j=0;
	int k=0;
	int cnt=0;
	int sum[20]={0,};
	int result =0;

	while(1)
	{
		if(cnt==2)
		{
			result = num[0]*10+num[1];
			break;
		}

		len--;
		j=0;
		for(i=0; i<len; i++)
		{
			sum[j] = (num[i]+num[i+1])%10;
			j++;
		}
		cnt = j;
		j--;
		while(1)
		{
			if(j < 0)
			{
				break;
			}
			num[j] = sum[j];
			j--;

		}

	}

	return result;
}

int characterCnt(char word)
{
	int cnt =0;

	switch(word)
	{
		case 'J':
			cnt = 2;
			break;
		case 'G':
			cnt = 3;
			break;
		case 'K':
			cnt = 3;
			break;
		case 'I':
			cnt = 3;
			break;
		case 'M':
			cnt = 4;
			break;
		case 'E':
			cnt = 4;
			break;
		case 'C':
			cnt = 1;
			break;
		case 'S':
			cnt = 1;
			break;
		case 'N':
			cnt = 3;
			break;
		case 'W':
			cnt = 4;
			break;
		case 'A':
			cnt = 3;
			break;
		case 'F':
			cnt = 3;
			break;
		case 'H':
			cnt = 3;
			break;
		case 'R':
			cnt = 3;
			break;
		case 'O':
			cnt = 1;
			break;
		case 'L':
			cnt = 2;
			break;
	}
	return cnt;
}

int crossAssign(char *nameOne, char *nameTwo, int *num)
{

	int len1 =0;
	int len2 =0;
	int len = 0;
	int i=0;
	int j=0;
	int k=0;
	char name[20]={0,};


	len = strlen(nameOne)*2;

	for(i=0; i<len; i++)
	{
		if(i%2==0)
		{
			name[i] = nameOne[j];
			j++;
		}
		else
		{
			name[i] = nameTwo[k];
			k++;
		}
	}

	for(i=0; i<len; i++)
	{
		printf("%c", name[i]);
		num[i]= characterCnt(name[i]);
		printf("%d", num[i]);
	}


}

int makeSameLength(char *nameOne, char *nameTwo)
{
	char name[20]={0,};
	int len1 =0;
	int len2 =0;
	int len = 0;
	int i=0;
	int j=0;
	int k=0;

	len1 = strlen(nameOne);
	len2 = strlen(nameTwo);

	if(len1 != len2)
	{
		if(len1>len2)
		{
			len = len1*2;
			for(i=0; i<len1-len2; i++)
			{
				nameTwo[len2+i] = nameTwo[i];
			}
		}
		else
		{
			len = len2*2;
			for(i=0; i<len2-len1; i++)
			{
				nameOne[len1+i] = nameOne[i];
			}
		}
	}
	else
	{
		len = len1*2;
	}

}
