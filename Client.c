#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* Args: ./client <UDP Hostname> <UDP Port> */
int main(int argc, char **argv){




	if(argc != 3){
		perror("Error: Client Syntax: ./Client <UDP Hostname> <UDP Port>")
	}
	return 0;
}
