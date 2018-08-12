#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
/*
두 문자열이 주어졌을 때, 두 문자열에 모두 포함된 가장 긴 공통 부분 문자열을 찾는 프로그램을 작성하시오.
어떤 문자열 s의 부분 문자열 t란, s에 t가 연속으로 나타나는 것을 말한다.
예를 들어, 문자열 ABRACADABRA의 부분 문자열은 ABRA, RAC, D, ACADABRA, ABRACADABRA, 빈 문자열 등이다.
하지만, ABRC, RAA, BA, K는 부분 문자열이 아니다.
두 문자열 ABRACADABRA와 ECADADABRBCRDARA의 공통 부분 문자열은 CA, CADA, ADABR, 빈 문자열 등이 있다.
이 중에서 가장 긴 공통 부분 문자열은 ADABR이며, 길이는 5이다.
또, 두 문자열이 UPWJCIRUCAXIIRGL와 SBQNYBSBZDFNEV인 경우에는 가장 긴 공통 부분 문자열은 빈 문자열이다.
*/
//ABRACADABRA
//ECADADABRBCRDARA

int main(void)
{
	char str1[100] = {0,};
	char str2[100] = {0,};
	int unit = 0;
	int i, j =0;
	int m=0;
	int n=0;
	int len1, len2 =0;
	int sameStr[100][20]={0,};
	int maxLen = 0;
	char maxStr[100] ={0,};

	scanf("%s", str1); //ABRACADABRA
	scanf("%s", str2); //ECADADABRBCRDARA

	len1 = strlen(str1);
	len2 = strlen(str2);

	for(i=0; i<len1; i++)
	{
		for(unit =1; unit<=len1; unit++)
		{
			if(i+unit >= len1)
			{
				break;
			}
			for(j=0; j<len2; j++)
			{
				if(memcmp(&str1[i], &str2[j], unit)==0)
				{
					for( n=0; n<m; n++)
					{
						if(memcmp(sameStr[n], &str2[j], unit)==0 && (strlen(sameStr[n])==unit))
						{
							break;
						}
					}
					if(n==m)
					{
						memcpy(sameStr[m], &str2[j], unit);
						m++;
					}
				}
			}
		}
	}

	for(i=0; i<m; i++)
	{
		if(maxLen < strlen(sameStr[i]))
		{
			maxLen = strlen(sameStr[i]);
			strcpy(maxStr, &sameStr[i]);
		}
	}
	printf("maxLen = %d, maxStr = %s\n", maxLen, maxStr);
}
