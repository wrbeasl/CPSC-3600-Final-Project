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

class http {
   private:
      char *server_name;
   	  char *robotID;
      uint16_t port;
      char *dir;	   // The server directory 
      FILE *page;  	   // The file that the request is asking for
      char *file;	   // The file name
      char *method;    // The method called by the client (GET | HEAD)
      char *ext;
      int  file_size;
      
      int sock;
      int connfd;
      struct sockaddr_in servaddr;

   public:
      http();
      http(int port, char *servername, char *robotID);
      ~http();

};