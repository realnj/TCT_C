#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <pthread.h>

#define BUFSIZE 1024
#define PORT 1111

int send_message(char * message);
int recv_message(char * message);
void error_handling(char * message);
void connectServer();

#endif /* SERVER_H_ */
