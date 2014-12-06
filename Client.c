#include "Common.h"

char *Commands[25] = {"GPS","DGPS","MOVE","sleep 5 seconds","STOP", "sleep 1 seconds", "GPS", "DGPS","TURN","sleep", "sleep 1 seconds", 
"GPS", "DGPS", "STOP", "sleep 1 seconds", "GPS", "DGPS", "MOVE", "sleep", "STOP", "sleep 1 seconds", "GPS","DGPS" };

/* Args: ./client <UDP Hostname> <UDP Port> */
int main(int argc, char **argv){

	int sock, port, curr_command;
	char *Servername;

	struct sockaddr_in serveraddr;

	if(argc != 3){
		perror("Error: Client Syntax: ./Client <UDP Hostname> <UDP Port>\n");
		exit(0);
	}

	port = atoi(argv[2]);
	Servername = argv[1];

	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror("Error creating socket, please panic.\n");
		exit(1);
	}


	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(Servername);
	serveraddr.sin_port = port;

	while(1){
		if(sendto(sock, Commands[curr_command], sizeof(Commands[curr_command]), 0, (struct sockaddr_in *) &serveraddr, sizeof(serveraddr)) < 0){

		}

	}



	return 0;
}
