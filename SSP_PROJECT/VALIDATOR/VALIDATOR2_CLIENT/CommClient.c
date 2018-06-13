#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <dirent.h>
#include "CommClient.h"
#include "inspection.h"
#include "utils.h"

#define IPADDR "127.0.0.1"
#define BUF_SIZE 4096

int SendToServer(char *inspectorID)
{
	int c_socket;
	struct sockaddr_in c_addr;
	const int port = 1111;
	char sendBuf[BUF_SIZE] ={0,};
	char szFoundFile[256]={0,};
	char szFindPath[256]={0,};
	char szMoveFile[256]={0,};
	struct dirent *de;
	int iSendResult;
	FILE *fp;
	int nSendLen;
	int nReadLen;
	int nFileSize;

	c_socket = socket(PF_INET, SOCK_STREAM, 0);

	 if(c_socket == -1)
	  error_handling("socket() error");

	 memset(&c_addr, 0, sizeof(c_addr));
	 c_addr.sin_family = AF_INET;
	 c_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	 c_addr.sin_port=htons(port);

	 if(connect(c_socket,(struct sockaddr*)&c_addr, sizeof(c_addr)) == -1)
	 {
		 error_handling("connect() error!");
		 close(c_socket);
		 return -1;
	 }

	 // send files
	 sprintf(szFindPath, "..//%s", inspectorID);
	 DIR *dr = opendir(szFindPath);
	 if(dr == NULL)
	 {
		 printf("Could not open current directory\n");
		 return -1;
	 }

	 while((de = readdir(dr)) != NULL)
	 {
		 if(de->d_type != DT_REG)
			 continue;

		 sprintf(szFoundFile, "..//%s//%s", inspectorID, de->d_name);

		 fp = fopen(szFoundFile, "rb");
		 if(!fp)
		 {
			 printf("file open error\n");
			 return -1;
		 }

		 //Send File Name
		 memset(sendBuf, 0x00, BUF_SIZE);
		 sprintf(sendBuf, "*%s", de->d_name);
		 nFileSize = get_file_size(fp);
		 printf("nFileSize = %d\n", nFileSize);
		 nSendLen = strlen(sendBuf)+sizeof(int);
		 int len = strlen(sendBuf);
		 sprintf(&sendBuf[strlen(sendBuf)], "%d", nFileSize);
//		 sendBuf[nSendLen] = '\0';
		 iSendResult = write(c_socket, sendBuf, nSendLen);
		 if(iSendResult == -1)
		 {
			 printf("send failed with error\n");
			 close(c_socket);
			 return -1;
		 }

		 memset(sendBuf, 0, BUF_SIZE);
		 while((nReadLen = fread(sendBuf, 1, BUF_SIZE, fp)) >0)
		 {
			// printf("//sendBuf =%s\n", sendBuf);
			 iSendResult = write(c_socket, sendBuf, nReadLen);
			 if(iSendResult == -1)
			 {
				 printf("send failed with error\n");
				 close(c_socket);
				 return -1;
			 }
		 }
		 fclose(fp);

		 //file move
		 sprintf(szMoveFile, "..//BACKUP//%s", de->d_name);
		 MoveFiles(szFoundFile, szMoveFile);
	 }
	 printf("finish\n");
	 closedir(dr);

	 close(c_socket);

	 return 1;

}

void error_handling(char * message)
{
	 fputs(message ,stderr);
	 fputc('\n', stderr);
}


