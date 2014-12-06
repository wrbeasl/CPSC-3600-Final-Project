#include "Common.h"

/* Args: ./client <UDP Hostname> <UDP Port> */
int main(int argc, char **argv){

	int sock, port;
	char *Servername;

	struct sockaddr_in serveraddr;
	robot_cmd command;
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

	command.command = cmdcode;
	command.value = cmdvalue;

	sendto(sock, &command, sizeof(command), 0,
	(struct sockaddr *) &serveraddr, sizeof(serveraddr));

	

	return 0;
}
