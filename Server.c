#include "Common.h"

int main(int argc, char **argv){

	int sock, port;
	char *RobotID;
	char *HostName;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	int clientLen, msgSize;
	char *Buffer[65535];


	if(argc != 4){
		perror("Error: Invalid Syntax, please use: ./Server <Robot ID> <Robot Hostname> <UDP Port>");
		exit(0);
	} 

	port = atoi(argv[3]);
	RobotID = argv[1];
	HostName = argv[2];

	//Sock check
	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror("Error: Failed to open the socket.\n");
		exit(0);
	}

	//Server address setup
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_port = port;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_family = AF_INET;

	printf("Binding to port %d\n", port);
	if(bind(sock, (struct serveraddr *) &serveraddr), sizeof(serveraddr) < 0){
		perror("Error binding server to port %d\n", port);
		exit(2);
	}

	for(;;){
		clientLen = sizeof(clientaddr);

		if((msgSize = recvfrom(sock, Buffer, 65535, 0, (struct sockaddr *) &clientaddr, &clientLen)) < 0){
			perror("Error: Failed to recieve from client.\n");
			exit(1);
		}

		
	}

	fflush(stdout);
	close(sock);
	return 0;
}