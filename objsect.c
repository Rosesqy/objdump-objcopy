#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "bfd.h"


static char *default_target = "elf64-x86-64";
char *sep = "  ";
char *nextln = "\n";


char *long_to_string(unsigned long val, char *temp){

	int i = 0;
	char *base = "0123456789abcdef";

	while(val){
		temp[i++] = base[val%16];
		val /= 16;
	}

	// char *stringnow = '0000000000000000';
	// for(int j = 0; j<16;j++){
	// 	stringnow[j] = temp[15-]
	// }
	
	return temp;
}

void print_objdump(bfd *abfd, asection *sect, void *obj){

	const char *namep;
	// //create a space for later temporary string
	// char *temp = malloc(16*sizeof(char));
	//initialize a temp charset for later use
	char temp[16] = {0};

	namep = bfd_section_name(abfd,sect);
	write(1,namep,strlen(namep));	
	write(1,sep,strlen(sep));

	// bfd_vma vma = bfd_section_vma(abfd,sect);
	// printf("%lx  ",vma);
	char *vma = long_to_string(bfd_section_vma(abfd,sect),temp);
	// write(1,&vma,sizeof(vma));
	write(1,vma,strlen(vma));
	write(1,sep,strlen(sep));

	unsigned long rawsize = bfd_section_size(abfd, sect);
	// write(1,&size, sizeof(size));
	char *size = long_to_string(rawsize,temp);
	write(1,size,strlen(size));
	write(1,sep,strlen(sep));

	long store = bfd_get_symtab_upper_bound(abfd);
	asymbol **loc = NULL;
	loc = malloc(store);
	long rawlocation = bfd_canonicalize_symtab(abfd, loc);
	// printf("%lx",location);
	// write(1,&location,sizeof(location));
	char *location = long_to_string(rawlocation,temp);
	write(1,location,strlen(location));
	write(1,nextln,strlen(nextln));
}

