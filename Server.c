#include "Common.h"

int main(int argc, char **argv){


	if(argc != 4){
		perror("Error: Invalid Syntax, please use: ./Server <Robot ID> <Robot Hostname> <UDP Port>");
		exit(0);
	}

	return 0;
}