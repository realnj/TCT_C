#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void printList(int list[]);
void addList(int result[], int input1[], int input2[]);

int main(void)
{
	int input1[3] = {7,1,6};
	int input2[3] = {5,9,2};
	int result[3] = {0,};

	printList(input1);
	printList(input2);

	// 두개의 배열에 저장된 숫자를 역순으로 꺼내 합한다.
	addList(result, input1, input2);
	printList(result);
}

void addList(int result[], int input1[], int input2[])
{
	int i =0;
	int num1=0;
	int num2=0;
	int tmp=1;
	int tmp1=1;
	int cnt=0;
	int sum=0;
	char buf[3]={0,};

	for(i=2; i>=0; i--)
	{
		cnt = i;
	    while(cnt>0)
	    {
	    	tmp *=10;
	    	cnt--;
	    }
		num1 += input1[i]*tmp;
		num2 += input2[i]*tmp;
		tmp=1;
	}

	sum = num1+num2;
	sprintf(buf, "%d", sum);

	for(i=0; i<3; i++)
	{
		result[2-i] = buf[i]-0x30;
	}

	/*
	for(i=2; i>=0; i--)
	{
		tmp = sum;
		cnt=i;
		while(cnt>0)
		{
			tmp /= 10;
			tmp1 *=10;
			cnt--;
		}
		result[i] = tmp;
		sum -= tmp*tmp1;
		tmp1 =1;
	}
	*/
}

void printList(int list[])
{
	printf("[");
	for(int i=0; i<3; i++)
	{
		printf("%d", list[i]);
		if(i !=2)
			printf(",");
	}
	printf("]\n");
}
