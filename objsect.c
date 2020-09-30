#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include "bfd.h"


static char *default_target = "elf64-x86-64";
char *sep = "  ";
char *tab = "\t";
static char *nextln = "\n";


char *long_to_string(unsigned long val, char *temp){

	int i = 0;
	char *base = "0123456789abcdef";
	char stringnow[16] = {0};

	// while(val){
	// 	temp[i++] = base[val%16];
	// 	val /= 16;
	// }

	while(val){
		stringnow[i++] = base[val%16];
		val /= 16;
	}

	stringnow[16] = '\0';
	//write(1,stringnow,strlen(stringnow));
	
	int j;
	// char *stringnow = malloc(strlen(temp));
	//char *stringnow = "0000000000000000";
	//fill the terminator firstly
	temp[16] = '\0';
	for(j = strlen(stringnow)-1; j >=0;j--){
		temp[j] = stringnow[15-j];
	}
	
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
	if (strlen(namep) < 16){
		write(1,tab,strlen(tab));}
	if(strlen(namep)<8){
		write(1,tab,strlen(tab));
	}
	write(1,sep,strlen(sep));

	// bfd_vma vma = bfd_section_vma(abfd,sect);
	// char *vma = long_to_string(bfd_section_vma(abfd,sect),temp);
	char *vma = long_to_string(sect->vma,temp);
	// write(1,&vma,sizeof(vma));
	write(1,vma,strlen(vma));
	write(1,sep,strlen(sep));

	// unsigned long rawsize = bfd_section_size(abfd, sect);
	unsigned long rawsize = sect->size;
	// write(1,&size, sizeof(size));
	char *size = long_to_string(rawsize,temp);
	write(1,size,strlen(size));
	write(1,sep,strlen(sep));

	// long store = bfd_get_symtab_upper_bound(abfd);
	// asymbol **loc = NULL;
	// loc = malloc(store);
	// long rawlocation = bfd_canonicalize_symtab(abfd, loc);
	unsigned long rawlocation = sect->filepos;
	char *location = long_to_string(rawlocation,temp);
	write(1,location,strlen(location));
	write(1,nextln,strlen(nextln));
}

bool enter_objsect(char *inputf){
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
		char *hds = "Sections:\nName          	VMA      Size          Position\n";
		write(1,hds,strlen(hds));
		bfd_map_over_sections(abfd, print_objdump, NULL);
	}
	else{
		char *nobject = ": the file is not recognized as a valid object file\n";
		write(1,inputf,strlen(inputf));
		write(1,nobject,strlen(nobject));
		return false;
	}
	return true;
}

