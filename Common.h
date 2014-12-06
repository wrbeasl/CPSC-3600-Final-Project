/*
 * Header File with appropriate includes
*/

#include <cstdlib>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/stat.h>

#define N 6

typedef struct http_struct {
   char *server_name;
   char *robotID;
   uint16_t port;
   int sock;
   int connfd;
   struct sockaddr_in servaddr;
} http;
