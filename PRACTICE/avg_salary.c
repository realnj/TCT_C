#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

typedef struct sal
{
	int empno;
	int salary;
}SAL;

typedef struct emp
{
	int empno;
	char empName[10];
	char level[10];
}EMP;

typedef struct type
{
	char level[10];
	int salary;
	int cnt;
	int avg;
}TYPE;

TYPE stType[10];

int compare_func_aes(const void*a, const void *b);
int main(void)
{
	SAL stSal[] ={23561, 5600,
						 37123, 4100,
						 33777, 4400,
						 13451, 6300,
						 23579, 5900,
						 87594, 2400,
						 59545, 3500,
						 49376, 3600};

	EMP stEmp[] ={ 59545, "나연", "대리",
							 37123 , "정연", "대리",
							 23561, "모모", "과장",
							 33777, "사나", "과장",
							 23579, "지효", "차장",
							 87594, "미나", "사원",
							 13451, "다현", "부장",
							 49376, "채영", "대리"};

	int i, j=0;
	int nCount=0;

    // 직급, 평균연봉으로 구성된 직급별 평균연봉정보를 출력
	// 평균연봉 오름차순
	// 평균연봉은 만원단위에서 반올림하여 처리한다.

	for(i=0; i<8; i++)
	{
		for(j=0; j<nCount; j++)
		{
			if(strcmp(stType[j].level, stEmp[i].level)==0)
			{
				stType[j].cnt++;
				break;
			}
		}

		if(j==nCount)
		{
			strcpy(stType[j].level, stEmp[i].level);
			stType[j].cnt =1;
			nCount++;
		}
	}

	for(i=0; i<8; i++)
	{
		for(int m=0; m<8; m++)
		{
			if(stSal[i].empno == stEmp[m].empno)
			{
				for(j=0; j<5; j++)
				{
					if(strcmp(stEmp[m].level, stType[j].level)==0)
					{
						stType[j].salary += stSal[i].salary;
					}
				}
			}
		}
	}

	for(i=0; i<nCount; i++)
	{
		stType[i].avg = stType[i].salary / stType[i].cnt;
	}

	qsort(stType, 5, sizeof(TYPE), compare_func_aes);

	printf("=====================\n");
	for(i=0; i<nCount; i++)
	{
		printf("직급 : %s 평균연봉 %d\n", stType[i].level, stType[i].avg);
	}
}

int compare_func_aes(const void *a, const void *b)
{
	TYPE *left = (TYPE *)a;
	TYPE *right = (TYPE *)b;

	if(left->avg > right->avg)
	{
		return 1;
	}
	else if(left->avg < right->avg)
	{
		return -1;
	}
	return 0;
}
