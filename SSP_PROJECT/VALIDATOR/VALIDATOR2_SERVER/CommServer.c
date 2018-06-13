#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include "CommServer.h"

#define DEFAULT_BUFLEN 4096
#define FILENAME_LEN 27
#define HEADER_LEN (1+FILENAME_LEN+4)


void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

int s_socket;
void *pThreadFunc(void *arg)
{
//	const int port = 27015;
	const int port = 1111;
	int c_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int recvLen;
	char recvBuf[DEFAULT_BUFLEN*2];
	int nBufIndex = 0;
	int cnt = 0;
	int nDataSize = 0;
	char filename[100]={0,};
	char szFullPath[256]={0,};

	s_socket = socket(PF_INET, SOCK_STREAM, 0);
	 memset(&s_addr, 0, sizeof(s_addr));
	 s_addr.sin_addr.s_addr= htonl(INADDR_ANY);
	 s_addr.sin_family = AF_INET;
	 s_addr.sin_port=htons(port);

	 if(bind(s_socket, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1)
	 {
		 printf("Can not bind\n");
		 return NULL;
	 }

	 if(listen(s_socket, 5)==-1)
	 {
		 printf("listen fail\n");
		 return NULL;
	 }

	 while(1)
	 {
		 len = sizeof(c_addr);
		 c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len );

		 if(c_socket == -1)
		 {
			 close(s_socket);
			 return NULL;
		 }

		 nBufIndex = 0;
		 cnt = 0;
		 nDataSize = 0;

		 while((recvLen = read(c_socket, &recvBuf[nBufIndex], DEFAULT_BUFLEN))>0)
		 {
//			 printf("&recvBuf[%d]= %s\n", nBufIndex, &recvBuf[nBufIndex]);
			 recvLen += nBufIndex;

			 while(cnt<recvLen)
			 {
				 if(recvBuf[cnt]== '*')
				 {
					 if(recvLen - cnt < HEADER_LEN)
					 {
						 memcpy(recvBuf, &recvBuf[cnt], recvLen - cnt);
						 nBufIndex = recvLen - cnt;
						 cnt = 0;
						 break;
					 }
					 cnt++;

					 memcpy(filename, &recvBuf[cnt], FILENAME_LEN);
					 filename[FILENAME_LEN] = 0;
					 cnt += FILENAME_LEN;

					 memcpy(&nDataSize, &recvBuf[cnt], sizeof(int));
					 cnt += sizeof(int);

					 if(cnt == recvLen)
					 {
						 cnt = 0;
						 nBufIndex= 0;
						 break;
					 }
				 }

				 if(recvLen - cnt <= nDataSize)
				 {
					 sprintf(szFullPath, "..\\SERVER\\%s", filename);
					 SaveReceiveFile(szFullPath, &recvBuf[cnt], recvLen-cnt);
					 nDataSize -= recvLen -cnt;
					 cnt = 0;
					 nBufIndex = 0;
					 break;
				 }
				 else
				 {
					 sprintf(szFullPath, "..\\SERVER\\%s", filename);
					 SaveReceiveFile(szFullPath, &recvBuf[cnt], nDataSize);
					 cnt += nDataSize;
					 nDataSize = 0;
				 }
			 }
		 }

		 close(c_socket);
	 }
	 close(s_socket);
}

void SaveReceiveFile(char *szFullPath, char *buf, int nLen)
{
	FILE *fp;
	fp = fopen(szFullPath, "ab");
	if(!fp)
	{
		return;
	}

	fwrite(buf, 1, nLen, fp);
	fclose(fp);
}
