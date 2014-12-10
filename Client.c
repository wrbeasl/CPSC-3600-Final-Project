/*
 * William Beasley, Chris Ragan, William Boatman, Mike Dozier, Jeff Grabowski
 * Client.c
 * UDP Client
 *
 */


#include "Common.h"
#define RECBUFSIZE 65535
int commands[22] = {1, 2, 3, 4, 6, 4, 1, 2, 5, 4, 1,
					 2, 6, 4, 1, 2, 3, 4, 6, 4, 1, 2};
int sleepTimes[6] = {5, 1, 1, 1, 5, 1};
/* Args: ./client <UDP Hostname> <UDP Port> */
int main(int argc, char **argv){

	int sock, port;
	char *Servername;
	void *buffer = malloc(sizeof(robot_cmd));
	void *recvbuffer = malloc(RECBUFSIZE);
	struct sockaddr_in serveraddr;
	struct sockaddr_in returnaddr;
	unsigned int returnsize;
	robot_cmd *command = buffer;
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
	serveraddr.sin_port = htons(port);

	//int validcommand = 0;
	int cmdcode;
	int cmdvalue = 0;
	int j = 0;

	for(int i = 0; i < 22; ++i){
		cmdcode = commands[i];
		if(cmdcode == 4){
			sleep(sleepTimes[j]);
			j++;
			continue;
		}
		command->command = cmdcode;
		command->value = cmdvalue;

		sendto(sock, buffer, sizeof(command), 0,
				 (struct sockaddr *) &serveraddr, sizeof(serveraddr));

		//printf("Sent %d bytes\n",i);

		returnsize = sizeof(returnaddr);
		recvfrom(sock, recvbuffer, RECBUFSIZE, 0, NULL, NULL);
		if(cmdcode < 3) //cmd is gps or dgps
		{
			printf("%s\n",(char*)recvbuffer);
		}
	}
	return 0;
}
