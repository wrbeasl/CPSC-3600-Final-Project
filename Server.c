/*
 * William Beasley, Chris Ragan, William Boatman, Mike Dozier, Jeff Grabowski
 * Server.c
 * UDP Server
*/

#include "Common.h"

void sendResponse(int sock, struct sockaddr_in client, char* response);
char *get_http(robot_cmd *command, char *hostname);
char *build_http_request(int command, char *hostname);
char *send_and_receieve_http(int command, char *request);
char *parse_http_response(char *response);

int main(int argc, char **argv){

	int sock, port;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	unsigned int clientLen;
	int msgSize;
	char Buffer[65535];


	if(argc != 4){
		perror("Error: Invalid Syntax, please use: ./Server <Robot ID> <Robot Hostname> <UDP Port>");
		exit(0);
	} 

	char *RobotID = (char *)malloc(strlen(argv[1]));
	char *HostName = (char *)malloc(strlen(argv[1]));

	port = atoi(argv[3]);
	memcpy(RobotID, argv[1], strlen(argv[1]));
	memcpy(HostName, argv[2], strlen(argv[2]));

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
		fflush(stdout);
		clientLen = sizeof(clientaddr);

		if((msgSize = recvfrom(sock, Buffer, 65535, 0, 
									  (struct sockaddr *) &clientaddr, &clientLen)) < 0) {
			perror("Error: Failed to recieve from client.\n");
			exit(1);
		} 
		robot_cmd *command = (robot_cmd *)Buffer;
		
		char *cmd = get_http(command, HostName);
		sendResponse(sock, clientaddr, cmd);
		//printf("%s", cmd);
	}

	
	close(sock);
	return 0;
}


void sendResponse(int sock, struct sockaddr_in client, char *response){
	if(sendto(sock, response, strlen(response), 0, (struct sockaddr *) &client, 
				 sizeof(client)) < 0){
		perror("Error: Failed to send response to the client.\n");
		exit(1);
	}
}

char *get_http(robot_cmd *command, char *hostname) {
	if(command->command == 4) {
		sleep(command->value);
		return NULL;
	}
	
	char *request = build_http_request(command->command, hostname);
	//printf("Sending request: \n%s\n", request);
/*	fp = popen(addr, "r");
	fgets(get_commands, 65535, fp);
	pclose(fp);
	*/
	char *response = send_and_receieve_http(command->command, request);
	char *answer = parse_http_response(response);
	return(answer);
}

char *build_http_request(int command, char *hostname) {
	char *start_request = "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n";
	char *host = "http://130.127.192.62";
	char *page = (char *)malloc(22);
	char *get_request = (char *)malloc(1023);
	switch(command) {
		case 1:
			strcpy(page, "/state?id=");
			strcat(page, hostname);
			sprintf(get_request, start_request, page, host);
			break;
		case 2:
			strcpy(page, "/state?id=");
			strcat(page, hostname);
			sprintf(get_request, start_request, page, host);
			break;
		case 3:
			strcpy(page, "/twist?id=");
			strcat(page, hostname);
			strcat(page, "&lx=4");
			sprintf(get_request, start_request, page, host);
			break;
		case 5:
			strcpy(page, "/twist?id=");
			strcat(page, hostname);
			strcat(page, "&az=30");
			sprintf(get_request, start_request, page, host);
			break;
		case 6:
			strcpy(page, "/twist?id=");
			strcat(page, hostname);
			strcat(page, "&lx=0");
			sprintf(get_request, start_request, page, host);
	}
	free(page);
	return(get_request);
}

char *send_and_receieve_http(int command, char *request) {
	int sock;
	char *buffer = (char *)malloc(1023);
	struct sockaddr_in *http = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in *));
	char *host = "130.127.192.62";
	if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("Failed to create http request socket\n");
		exit(1);
	}
	
	http->sin_family = AF_INET;
	switch(command) {
		case 2:
			http->sin_port = htons(8084);
			break;
		case 1: case 3: case 5: case 6:
			http->sin_port = htons(8082);
			break;
	}
	inet_pton(AF_INET, host, (void *)(&(http->sin_addr.s_addr)));
	
	if(connect(sock, (struct sockaddr *)http, sizeof(struct sockaddr)) < 0){
		perror("Failed connecting to the host\n");
		exit(1);
	}
	if(send(sock, request, strlen(request), 0) < 0) {
		perror("Nothing was sent to the server\n");
		exit(1);
	}
	
	int recvd = 0;
	bzero(buffer, 1023);
	while((recvd = recv(sock, buffer, 1023, 0)) > 0) {
		
	}
	//printf("buffer: \n%s\n", buffer);
	return(buffer);
}

char *parse_http_response(char *response) {
	char *temp = (char *)malloc(127);
	char *tok = strtok(response, "\r\n\r\n");
	while(tok != NULL) {
		strcpy(temp, tok);
		tok = strtok(NULL, "\r\n");
	}
	return(temp);
}