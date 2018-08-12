#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
/*
�� ���ڿ��� �־����� ��, �� ���ڿ��� ��� ���Ե� ���� �� ���� �κ� ���ڿ��� ã�� ���α׷��� �ۼ��Ͻÿ�.
� ���ڿ� s�� �κ� ���ڿ� t��, s�� t�� �������� ��Ÿ���� ���� ���Ѵ�.
���� ���, ���ڿ� ABRACADABRA�� �κ� ���ڿ��� ABRA, RAC, D, ACADABRA, ABRACADABRA, �� ���ڿ� ���̴�.
������, ABRC, RAA, BA, K�� �κ� ���ڿ��� �ƴϴ�.
�� ���ڿ� ABRACADABRA�� ECADADABRBCRDARA�� ���� �κ� ���ڿ��� CA, CADA, ADABR, �� ���ڿ� ���� �ִ�.
�� �߿��� ���� �� ���� �κ� ���ڿ��� ADABR�̸�, ���̴� 5�̴�.
��, �� ���ڿ��� UPWJCIRUCAXIIRGL�� SBQNYBSBZDFNEV�� ��쿡�� ���� �� ���� �κ� ���ڿ��� �� ���ڿ��̴�.
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
