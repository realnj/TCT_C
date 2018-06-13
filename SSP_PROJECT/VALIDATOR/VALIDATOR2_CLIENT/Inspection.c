#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "utils.h"
#include "inspection.h"

void InspectCard(char *startTime, char *id, char *busID, char *cardInfo)
{
	char fileName[50]={0,};
	FILE *fp;
	char cardID[9]={0,};
	char cardBusID[8]={0,};
	char code;
	char rideTime[15] ={0,};

	char szValidateCode[3] ={0,};
	char szInspectTime[15] ={0,};
	char szFolder[80] ={0,};


	//parsing
	memcpy(cardID, &cardInfo[0], 8);
	memcpy(cardBusID, &cardInfo[8], 7);
	code = cardInfo[15];
	memcpy(rideTime, &cardInfo[16], 14);

	// Get Inspect Time
	GetCurrentDateTimeString(szInspectTime);

	// Validation
	if(strcmp(busID, cardBusID) != 0)
	{
		strcpy(szValidateCode, "R2");
	}
	else
	{
		if(code == 'N') // ����
		{
			if(HourDiff(rideTime, szInspectTime) < 3)
			{
				strcpy(szValidateCode, "R1");
			}
			else
			{
				strcpy(szValidateCode, "R4");
			}
		}
		else // ����
		{
			strcpy(szValidateCode, "R3");
		}
	}

	sprintf(szFolder, "../%s", id);
	mkdir(szFolder, 0777);

	sprintf(fileName, "%s/%s_%s.txt", szFolder, id, startTime);

	fp = fopen(fileName, "a++");

	fprintf(fp, "%.8s#%.7s#%s#%.2s#%.15s\n", id, busID, cardInfo, szValidateCode, szInspectTime);

	if(fp)
	{
		fclose(fp);
	}
}
