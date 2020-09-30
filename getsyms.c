#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "objsym.h"


static char *nextln = "\n";

int main(int argc, char **argv){

	if(argc != 2){
		char *instruct = "Usage: getsections filename\n";
		write(1,instruct,strlen(instruct));
		return 0;
	}

	if(enter_objsym(argv[1])){
		write(1,"PASS",5);
		write(1,nextln,strlen(nextln));
	}else{
		write(1,"FAIL",5);
		write(1,nextln,strlen(nextln));
	}
	
	return 0;
}
