#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "objsect.h"

static char *nextln = "\n";

int main(int argc, char **argv){
	//char *target = default_target;

	if(argc != 2){
		char *instruct = "Usage: getsections filename\n";
		// printf("Usage: getsections filename\n");
		write(1,instruct,strlen(instruct));
		write(1,nextln,strlen(nextln));
		return 0;
	}

	if(enter_objsect(argv[1])){
		write(1,"PASS",5);
		write(1,nextln,strlen(nextln));
	}else{
		write(1,"FAIL",5);
		write(1,nextln,strlen(nextln));
	}
	
	return 0;
}
