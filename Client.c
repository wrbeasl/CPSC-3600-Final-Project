#include "Common.h"

char *Commands[25] = {"GPS","DGPS","MOVE","sleep 5 seconds","STOP", "sleep 1 seconds", "GPS", "DGPS","TURN","sleep", "sleep 1 seconds", 
"GPS", "DGPS", "STOP", "sleep 1 seconds", "GPS", "DGPS", "MOVE", "sleep", "STOP", "sleep 1 seconds", "GPS","DGPS" };

/* Args: ./client <UDP Hostname> <UDP Port> */
int main(int argc, char **argv){

	int sock, port, curr_command;
	char *Servername;
	void *buffer = malloc(sizeof(robot_cmd));
	struct sockaddr_in serveraddr;
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
/*
	while(1){
		if(sendto(sock, Commands[curr_command], sizeof(Commands[curr_command]), 0, (struct sockaddr_in *) &serveraddr, sizeof(serveraddr)) < 0){

		}

	}
*/

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

	int i =	sendto(sock, buffer, sizeof(command), 0,
	(struct sockaddr *) &serveraddr, sizeof(serveraddr));

	printf("Sent %d bytes\n",i);

	return 0;
}
