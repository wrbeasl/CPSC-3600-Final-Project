#include "Common.h"

int sendResponse(int sock, int port, struct sockaddr_in client, char* response);

int main(int argc, char **argv){

	int sock, port;
	char *RobotID;
	char *HostName;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	unsigned int clientLen;
	int msgSize;
	char Buffer[65535];


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
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_family = AF_INET;

	//bind port
	printf("Binding to port %d\n", port);
	if(bind(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0){
		printf("Error binding server to port %d\n", port);
		exit(2);
	}

	//for loop infinite
	for(;;){
		clientLen = sizeof(clientaddr);

		if((msgSize = recvfrom(sock, Buffer, 65535, 0, (struct sockaddr *) &clientaddr, &clientLen)) < 0){
			perror("Error: Failed to recieve from client.\n");
			exit(1);
		} else {
			printf("Got");
		}
		robot_cmd *command = (robot_cmd *)Buffer;
		printf("%d, %d\n", command->command, command->value);

	}

	fflush(stdout);
	close(sock);
	return 0;
}



int sendResponse(int sock, int port, struct sockaddr_in client, char *response){
	if(sendto(sock, response, sizeof(response), 0, (struct sockaddr *) &client, sizeof(&client)) < 0){
		perror("Error: Failed to send response to the client.\n");
		return -1;
	} else {
		return 0;
	}
}
