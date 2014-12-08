/*
 * TODO: Figure out what we're going to do with messages once they come back
 * Need some way of identifying what type of data we just received back
 * 
 */


#include "Common.h"
#define RECBUFSIZE 65535
char *Commands[25] = {"GPS","DGPS","MOVE","sleep 5 seconds","STOP", "sleep 1 seconds", "GPS", "DGPS","TURN","sleep", "sleep 1 seconds", 
"GPS", "DGPS", "STOP", "sleep 1 seconds", "GPS", "DGPS", "MOVE", "sleep", "STOP", "sleep 1 seconds", "GPS","DGPS" };

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

	int validcommand = 0;
	int cmdcode;
	int cmdvalue = 0;

	while(!validcommand) {
		printf("Command? ");
		scanf("%d", &cmdcode);

		if(cmdcode > 0 && cmdcode < 7)
		{
			if(cmdcode == 4)
			{
				printf("\nSleep how long? ");
				scanf("%d",&cmdvalue);
			}
		validcommand = 1;
		}
	}

	command->command = cmdcode;
	command->value = cmdvalue;

	sendto(sock, buffer, sizeof(command), 0,
			 (struct sockaddr *) &serveraddr, sizeof(serveraddr));

	//printf("Sent %d bytes\n",i);

	returnsize = sizeof(returnaddr);
	recvfrom(sock, recvbuffer, RECBUFSIZE, 0, NULL, NULL);
	
	printf("%s\n",(char*)recvbuffer);

	return 0;
}
