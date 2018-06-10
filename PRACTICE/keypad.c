#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
bool setInitialKeypad(char *inputString);
bool validateInputKeypad(char *inputString);

int main(void)
{
	bool isValidPattern = false;
	char inputString[100];

	do{
		printf("====================================\n");
		printf("초기 숫자 암호를 입력해주세요 : ");
		gets(inputString);
		isValidPattern = setInitialKeypad(inputString);
		if(!isValidPattern)
		{
			printf("규칙에 맞는 암호가 아닙니다\n");
		}
	}while(!isValidPattern);

	do{
		printf("====================================\n");
		printf("검증을 위하여 다시 한번 입력해주세요 : ");
		gets(inputString);
		isValidPattern = validateInputKeypad(inputString);
		if(!isValidPattern)
		{
			printf("초기 숫자 암호와 다릅니다.\n");
		}
	}while(!isValidPattern);

	printf("====================================\n");
	printf("압호 검증을 완료했습니다.");
}

bool setInitialKeypad(char *inputString)
{
	//파일 저장 위치
	char *saveFilePath = "password.txt";
	FILE *fp;
	int i=0;
	int unit =0;
	//inputString에 포함된 숫자의 개수
	int numLength =0;
	//inputString을 "," 문자로 parsing한 결과
	char *num[20] ={0,};
	char str[20]={0,};
	char temp[100]={0,};
	int nArr[100] ={0,};
	strncpy(temp, inputString, strlen(inputString));
	for(num[numLength++] = strtok(temp, ",");
			(num[numLength]= strtok(NULL, ","))!=NULL; numLength++);

	printf("[입력문자열] %s\n", inputString);
	printf("[파싱결과]");
	for(int i=0; i<numLength; i++)
	{
		printf("%s", num[i]);
		str[i] = num[i][0];
		nArr[i] = atoi(num[i]);
	}
	printf("\n");

	printf("str= %s\n", str);
	/* 암호 길이는 6~15 */
	if(numLength < 6 || numLength > 15)
	{
		printf("길이가 잘못됨 numLength = %d\n", numLength);
		return false;
	}

	for(i=0; i<numLength; i++)
	{
		if(!(str[i] >= '0' && str[i] <='9'))
		{
			printf("숫자가 아님 \n");
			return false;
		}
	}

	for(i=2; i<numLength; i++)
	{
		if((nArr[i-2] == nArr[i-1]) && (nArr[i-1] == nArr[i]))
		{
			printf("3개 연속 동일한 숫자\n");
			return false;
		}
	}

	for(i=2; i<numLength; i++)
	{
		if(((nArr[i-2]+1)%10 == nArr[i-1]%10) && ((nArr[i-1]+1)%10 == nArr[i]%10))
		{
			printf("연속되는 숫자(+)\n");
			return false;
		}
	}

	for(i=2; i<numLength; i++)
	{
		if(((nArr[i-2]+10-1)%10 == nArr[i-1]%10) && ((nArr[i-1]+10-1)%10 == nArr[i]%10))
		{
			printf("연속되는 숫자(-)\n");
			return false;
		}
	}

	for(i=0; i<numLength; i++)
	{
		for(unit =2; unit<=numLength/2; unit++)
		{
			if(i+unit+unit > numLength)
			{
				printf("길이 초과\n");
				break;
			}
			if(memcmp(&str[i], &str[i+unit], unit)==0)
			{
				printf("pattern 찾음\n");
				return false;
			}
		}
	}

	fp = fopen(saveFilePath, "w");

	fprintf(fp, "%s", str);

	if(fp)
	{
		fclose(fp);
	}

	return true;

}

bool validateInputKeypad(char *inputString)
{
	char *loadFilePath = "password.txt";
	FILE *fp;
	//inputString에 포함된 숫자의 개수
	int numLength =0;
	//inputString을 "," 문자로 parsing한 결과
	char *num[10] ={0,};
	char temp[100]={0,};
	char buf[100]={0,};
	char str[100]={0,};
	strncpy(temp, inputString, strlen(inputString));
	for(num[numLength++] = strtok(temp, ",");
			(num[numLength]= strtok(NULL, ","))!=NULL; numLength++);

	printf("[입력문자열] %s\n", inputString);
	printf("[파싱결과]");
	for(int i=0; i<numLength; i++)
	{
		printf("%s", num[i]);
		str[i] = num[i][0];
	}
	printf("\n");

	fp = fopen(loadFilePath, "r");

	fgets(buf, 100, fp);

	if(memcmp(buf, str, numLength)!=0)
	{
		return false;
	}

	return true;
}

