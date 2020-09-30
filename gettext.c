#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "objcopy.h"
#include "bfd.h"

static const char* target = "elf64-x86-64";
static char *nextln = "\n";

int main(int argc, char **argv){

	if(argc != 2){
		char *instruct = "Usage: getsections filename\n";
		write(1,instruct,strlen(instruct));
		return 0;
	}

	asection *sect = enter_objcopy(argv[1]);

	if(sect){
		size_t size = sect->size;
		char text[size];
		bfd_get_section_contents(abfd, sect, text, 0, size);
		int fd = open("text-output", O_RDWR|O_CREAT);
		write(fd, text, strlen(text));
		close(fd);
		write(1,"PASS",5);
		write(1,nextln,strlen(nextln));
	}else{
		write(1,"FAIL",5);
		write(1,nextln,strlen(nextln));
	}
	
	return 0;
}
