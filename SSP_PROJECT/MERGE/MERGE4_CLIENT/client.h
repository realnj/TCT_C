#ifndef CLIENT_H_
#define CLIENT_H_

#define BUFSIZE 1024
#define NAMESIZE 100
#define PORT 1111

int send_message(char* message);
int recv_message(char* message);
int connectServer(char* clientName);
void error_handling(char * message);

