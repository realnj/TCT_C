#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "../VALIDATOR_UTIL/utils.h"
#include "CommServer.h"

int main()
{
	char szInput[20];
	pthread_t threadId;
	int nRet, status;

	if((nRet = pthread_create(&threadId, NULL, pThreadFunc, NULL)) != 0)
	{
		perror("pthread create error!\n");
		return -1;
	}

	while(1)
	{
		memset(szInput, 0, 20);
		fgets(szInput, 20, stdin);
		if(strncmp(szInput, "QUIT", 4) == 0)
		{
			 close(s_socket);
			 break;
		}

		usleep(1);
	}

	pthread_join(threadId, (void**)&status);

	return 0;

}
