#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include "bfd.h"

static char *default_target = "elf64-x86-64";
static char *sep = "  ";
static char *tab = "\t";
static char *nextln = "\n";

asection enter_objcopy(char *inputf){
	bfd_init();
	bfd *abfd;
	abfd = bfd_openr(inputf,default_target);

	if(abfd == NULL)
	{
		char *nfound = "File not found!\n";
		write(1,nfound,strlen(nfound));
		return false;
	}

	if (bfd_check_format(abfd, bfd_object))
	{
		//get all the .text sections
		asection *sect = bfd_get_section_by_name(abfd, ".text");
		return sect;
	}
	else{
		char *nobject = ": the file is not recognized as a valid object file\n";
		write(1,inputf,strlen(inputf));
		write(1,nobject,strlen(nobject));
		return false;
	}
	return true;
}

