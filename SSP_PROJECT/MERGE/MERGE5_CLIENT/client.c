#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "./client.h"

char name[NAMESIZE] = "[Default]";
int sock;

int connectServer(char* clientName)
{
	 struct sockaddr_in serv_addr;
	 pthread_t rcv_thread;
	 void* thread_result;

	 printf("connectServer\n");

	 sock = socket(PF_INET, SOCK_STREAM, 0);
	 if(sock == -1)
	  error_handling("socket() error");

	 memset(&serv_addr, 0, sizeof(serv_addr));
	 serv_addr.sin_family = AF_INET;
	 serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	 serv_addr.sin_port=htons(PORT);

	 if(connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	  error_handling("connect() error!");

	 return 0;
}

int send_message(char* message)
{
	int ret =0;
	printf("send message = %s\n", message);
	ret=write(sock, message, strlen(message));

	if(ret<0)
	{
		printf("write error\n");
	}
}

int recv_message(char* message)
{
	 char name_message[BUFSIZE];
	 int str_len;
	  str_len = read(sock, name_message, NAMESIZE+BUFSIZE-1);

//	  printf("strlen[%d]\n",str_len);

	  if(str_len <=0)
	  {
		  return (void*)0;
	  }
	  name_message[str_len]=0;
	  memcpy(message, name_message, str_len);
	  message[str_len] =0;

	  return str_len;
}

void error_handling(char * message)
{
	 fputs(message ,stderr);
	 fputc('\n', stderr);
}



