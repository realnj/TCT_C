#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "inspection.h"

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
int checkIdPwd(char *id, char *pwd);
int main(void)
{
	char szID[10] ={0,};
	char szPwd[10]={0,};
	char busID[10]={0,};
	char szTime[15] ={0,};
	char szCardInfo[50]={0,};
	char c =0;
	while(1)
	{
		scanf("%s %s", szID, szPwd);
		if(checkIdPwd(szID, szPwd))
		{
			printf("LOGIN SUCCESS\n");
			break;
		}
		{
			char c;
			while((c=getchar()) != '\n' && c!=EOF )
			{

			}
			printf("LOGIN FAIL\n");
		}
	}

	while(1)
	{
		scanf("%s", busID);

		if(strcmp(busID, "LOGOUT")==0)
		{
			printf("LOGOUT\n");
			break;
		}

		if(strlen(busID) < 7 || strncmp(busID, "BUS_", 4) != 0)
		{
			printf("Wrong Bus ID\n");
			while((c=getchar()) != '\n' && c != EOF)
			{

			}
			continue;
		}
		GetCurrentDateTimeString(szTime);
		printf("szTime = %s\n", szTime);

		while(1)
		{
			scanf("%s", szCardInfo);
			if(strcmp(szCardInfo, "DONE")==0)
			{
				break;
			}

			if(strlen(szCardInfo) != 30)
			{
				printf("Wrong Card Info\n");
				while((c=getchar()) != '\n' && c != EOF)
				{

				}
				continue;
			}

			InspectCard(szTime, szID, busID, szCardInfo);
		}
	}
	return 0;
}

int checkIdPwd(char *id, char *pwd)
{
	char fID[10] ={0,};
	char fPwd[100] ={0,};
//	char encPwd[100] ={0,};

//	GetHashSHA256(pwd, encPwd);

	FILE *fp;
	fp = fopen("../CLIENT/INSPECTOR.txt", "rt");
	if(!fp)
	{
		printf("file open fail\n");
		return 0;
	}

	while(fscanf(fp, "%s %s", fID, fPwd) != EOF )
	{
		if((strcmp(id, fID)==0) &&(strcmp(pwd, fPwd)==0))
		{
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);
	return 0;
}
