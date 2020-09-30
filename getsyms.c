#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
// #include <stdio.h>
#include "bfd.h"

// static char *default_target = NULL;
static char *default_target = "elf64-x86-64";
char *sep = "  ";
char *nextln = "\n";

static void print_nm(bfd *abfd, asection *sect, void *obj){
	
	const char *namep;

	namep = bfd_section_name(abfd,sect);
	write(1,namep,strlen(namep));	
	write(1,sep,strlen(sep));

	bfd_vma addr = bfd_section_vma(abfd,sect);
	// printf("%lx  ",addr);
	write(1,&addr,sizeof(addr));
	write(1,sep,strlen(sep));

	unsigned long size = bfd_section_size(abfd, sect);
	write(1,&size, sizeof(size));
	write(1,sep,strlen(sep));
	
	long store = bfd_get_symtab_upper_bound(abfd);
	// printf("%lx  ",size);
	// write(1,&store,sizeof(store));
	// write(1,sep,strlen(sep));
	asymbol **loc = NULL;
	loc = malloc(store);
	long location = bfd_canonicalize_symtab(abfd, loc);
	// printf("%lx",location);
	write(1,&location,sizeof(location));
	write(1,nextln,strlen(nextln));
}

int main(int argc, char **argv){
	char *target = default_target;

	if(argc != 2){
		char *instruct = "Usage: getsections filename\n";
		// printf("Usage: getsections filename\n");
		write(1,instruct,strlen(instruct));
		return 0;
	}

	//unsigned int bfd_init(void);
	bfd *abfd;
	abfd = bfd_openr (argv[1],default_target);

	if(abfd == NULL)
	{
		// printf("File not found!\n");
		char *nfound = "File not found!\n";
		write(1,nfound,strlen(nfound));
		return 0;
	}

	if (bfd_check_format(abfd, bfd_object))
	{
		char *hds = "Sections:\nName          	VMA      Size          Position\n";
		// printf("Sections:\n");
		// printf("Name          VMA      Size          Position\n");
		write(1,hds,strlen(hds));
		bfd_map_over_sections(abfd, print_nm, NULL);
	}
	else{
		char *nobject = ": the file is not recognized as a valid object file\n";
		// printf("%c: the file is not recognized as a valid object file\n",argv[1]);
		write(1,argv[1],strlen(argv[1]));
		write(1,nobject,strlen(nobject));
		return 0;
	}

	
	return 0;
}
