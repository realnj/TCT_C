

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "./server.h"

int clnt_number=0;
int clnt_sock;
pthread_mutex_t mutx;

void connectServer()
{
	 int serv_sock;
	 struct sockaddr_in serv_addr;
	 struct sockaddr_in clnt_addr;
	 int clnt_addr_size;

	 if(pthread_mutex_init(&mutx,NULL))
	  error_handling("mutex init error");

	 serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	 if(serv_sock == -1)
	  error_handling("socket() error");

	 memset(&serv_addr, 0, sizeof(serv_addr));
	 serv_addr.sin_family = AF_INET;
	 serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	 serv_addr.sin_port = htons(PORT);

	 if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	  error_handling("bind() error");

	 if(listen(serv_sock, 5) == -1)
	  error_handling("listen() error");

	  clnt_addr_size = sizeof(clnt_addr);
	  clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

}

int send_message(char * message)
{
	printf("[SERVER] send_message = %s\n", message);
	return  write(clnt_sock, message, strlen(message));
}

int recv_message(char *message)
{
	char recv_message[BUFSIZE]={0,};
	int str_len =0;

	str_len = recv(clnt_sock, recv_message, sizeof(recv_message), MSG_NOSIGNAL);

	if(str_len < 0)
	{
		printf("recv() failed\n");
		return 0;
	}
	else if(str_len ==0)
	{
		printf("closed by client\n");
		return 0;
	}
	else
	{
		recv_message[str_len] = '\0';
		memcpy(message, recv_message, str_len);
		message[str_len] ='\0';
		return str_len;
	}
}

void error_handling(char * message)
{
	 fputs(message, stderr);
	 fputc('\n',stderr);
	 exit(1);
}
