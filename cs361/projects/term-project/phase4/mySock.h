#ifndef MYSOCK_H_
#define MYSOCK_H_

void err_sys(const char* x) ;
void err_quit(const char* x)  ;
int clientUDPsock(const char *host, const char *service ) ;
int serverUDPsock(const unsigned short port) ;

typedef struct sockaddr SA ;
#define BASEPORT 50000   /* port base for non-root servers */

#endif
