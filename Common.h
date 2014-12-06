/*
 * Header File with appropriate includes
*/

#include <stdlib.h>
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

typedef struct robot_cmd {
	int command;
	int value;
}robot_cmd;


/* Command interface:
 *
 * GPS: 1
 * DGPS: 2
 * MOVE: 3
 * SLEEP: 4
 * TURN: 5
 * STOP: 6
 *
 */
