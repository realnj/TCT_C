#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}
int strCompact(char *str);
int checkMatchWord(char *str, char *pattern, int offset, int unit, int totalLen);
int replaceStr_unit(char *str, char *pattern, char *change, int unitLen);
int replaceStr(char *str, char *pattern, char *change);
//letsgogogo는 lets3(go)
//nowletsgogogoletsgogogo는 now2(lets3(go))
// nowletsgogogoletsgogogoandrunrunrun 은 now2(lets3(go))and3(run)

int main(void)
{
	char str[100]={0,};

	scanf("%s", str);

	printf("org = %s\n",str);
	strCompact(str);
	printf("change = %s\n",str);
	return 0;
}
int strCompact(char *str)
{
	int i=0;
	char pattern[100] ={0,};
	char change[100]={0,};
	int count =0;
	int totalLen =0;
	int unit=0;
	int unitLen=0;

	totalLen = strlen(str);

	for(i=0; i<totalLen; i++)
	{

		for(unit=1; unit<totalLen/2; unit++)
		{
			memset(pattern, 0x00, 100);
			memcpy(pattern, &str[i], unit);

			count = checkMatchWord(str, pattern, i, unit, totalLen);
			if(count > 0)
			{
				sprintf(change, "%d(%s)", count+1, pattern);
				unitLen = unit*(count+1);
				replaceStr_unit(str, pattern, change, unitLen);
				totalLen = strlen(str);
				i = -1;
				break;
			}
		}
	}
	return 0;
}

int checkMatchWord(char *str, char *tmp, int offset, int unit, int totalLen)
{
	int count=0;

	while(1)
	{

		if(offset+unit >= totalLen)
		{
			break;
		}

		if(tmp[0]== '(' || tmp[0] == ')')
		{
			break;
		}

		if(memcmp(tmp, &str[offset+unit], unit)==0)
		{
			count++;
//			printf("패턴 찾음 tmp = %s, count = %d\n", tmp, count);
			offset += unit;
		}
		else
		{
//			printf("없음\n");
			break;
		}

	}
	return count;

}

int replaceStr_unit(char *str, char *pattern, char *change, int unitLen)
{
	int i=0;
	int j=0;
	int len =0;
	char result[100]={0,};

	len = strlen(str);
	for(i=0; i<len; i++)
	{
		if(memcmp(&str[i], pattern, strlen(pattern))==0)
		{
			memcpy(&result[j], change, strlen(change));
			j += strlen(change);
			i += unitLen-1;
		}
		else
		{
			result[j] = str[i];
			j++;
		}
	}
	memset(str, 0x00, 100);
	memcpy(str, result, strlen(result));
	return 0;
}
