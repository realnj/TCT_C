
#ifndef COMMSERVER_H_
#define COMMSERVER_H_

extern int s_socket;
void *pThreadFunc(void *arg);
void SaveReceiveFile(char *szFullPath, char *buf, int nLen);

#endif /* COMMSERVER_H_ */
