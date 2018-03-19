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
		printf("�ʱ� ���� ��ȣ�� �Է����ּ��� : ");
		gets(inputString);
		isValidPattern = setInitialKeypad(inputString);
		if(!isValidPattern)
		{
			printf("��Ģ�� �´� ��ȣ�� �ƴմϴ�\n");
		}
	}while(!isValidPattern);

	do{
		printf("====================================\n");
		printf("������ ���Ͽ� �ٽ� �ѹ� �Է����ּ��� : ");
		gets(inputString);
		isValidPattern = validateInputKeypad(inputString);
		if(!isValidPattern)
		{
			printf("�ʱ� ���� ��ȣ�� �ٸ��ϴ�.\n");
		}
	}while(!isValidPattern);

	printf("====================================\n");
	printf("��ȣ ������ �Ϸ��߽��ϴ�.");
}


bool setInitialKeypad(char *inputString)
{
	//���� ���� ��ġ
	char *saveFilePath = "password.txt";
	int i=0;
	int unit=0;
	FILE *fp;
	//inputString�� ���Ե� ������ ����
	int numLength =0;
	//inputString�� "," ���ڷ� parsing�� ���
	char *num[10] ={0,};
	char temp[100]={0,};
	char str[100] ={0,};
	int nArr[100] ={0,};
	strncpy(temp, inputString, strlen(inputString));
	for(num[numLength++] = strtok(temp, ","); (num[numLength]= strtok(NULL, ","))!=NULL; numLength++);

	printf("[�Է¹��ڿ�] %s\n", inputString);
	printf("[�Ľ̰��]");

	for(int i=0; i<numLength; i++)
	{
		printf("%s", num[i]);
		strcpy(&str[i], num[i]);
		nArr[i] = atoi(num[i]);
	}
	printf("\n");

	if(numLength < 6 || numLength > 15)
	{
		printf("���̰� �߸��� numLength = %d\n", numLength);
		return false;
	}

	for(i=0; i<numLength; i++)
	{
		if(!(str[i] >= '0' && str[i] <= '9' ))
		{
			printf("���ڰ� �ƴ�\n");
			return false;
		}
	}

	for(i=0; i<numLength; i++)
	{
		for(unit=2; unit<numLength/2; unit++)
		{
			if(i + unit >= numLength)
			{
				break;
			}

			if(memcmp(&str[i], &str[i+unit], unit)==0)
			{
				printf("���� ã��\n");
				return false;
			}
		}
	}

	for(i=2; i<numLength; i++)
	{
		if((nArr[i-2]== nArr[i-1]) &&(nArr[i-1] == nArr[i]))
		{
			printf("������ ����\n");
			return false;
		}
	}

	for(i=2; i<numLength; i++)
	{
		if(((nArr[i-2]+1)%10 == nArr[i-1]%10) &&( (nArr[i-1]+1)%10 == nArr[i]%10))
		{
			printf("���ӵ� ����(+)\n");
			return false;
		}
	}

	for(i=2; i<numLength; i++)
	{
		if(((nArr[i-2]+10-1)%10 == nArr[i-1]%10) &&( (nArr[i-1]+10-1)%10 == nArr[i]%10))
		{
			printf("���ӵ� ����(-)\n");
			return false;
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
	int numLength =0;
	char *num[10] ={0,};
	char temp[100] ={0,};
	char str[100]={0,};
	char buf[20]={0,};
	strncpy(temp, inputString, strlen(inputString));
	for(num[numLength++] = strtok(temp, ","); (num[numLength]= strtok(NULL, ","))!=NULL; numLength++);

	printf("[�Է¹��ڿ�] %s\n", inputString);
	printf("[�Ľ̰��]");

	for(int i=0; i<numLength; i++)
	{
		printf("%s", num[i]);
		strcpy(&str[i], num[i]);
	}
	printf("\n");

	fp = fopen(loadFilePath, "r");

	fgets(buf, 20, fp);

	if(memcmp(buf, str, numLength)!=0)
	{
		return false;
	}

	if(fp)
	{
		fclose(fp);
	}

	return true;
}
