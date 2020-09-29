#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "bfd.h"

static char *default_target = NULL;

static void print_objdump(bfd *abfd, asection *sect, void *obj){
	char *sep = "  ";
	//char *s = sep;

        const char *namep;

	namep = bfd_section_name(abfd,sect);
	//printf("%s  ",namep);
	write(1,namep,strlen(namep));	
	write(1,sep,strlen(sep));
	bfd_vma addr = bfd_section_vma(abfd,sect);
	printf("%lx  ",addr);
	long size = bfd_get_symtab_upper_bound(abfd);
	printf("%lx  ",size);
	asymbol **loc = malloc(size);
	long location = bfd_canonicalize_symtab(abfd, loc);
	printf("%lx",location);
	write(1,nextln,strlen(nextln));
}

int main(int argc, char **argv){
	char *target = default_target;
	
	char *nextln = "\n";

	int fd[2];
	fd[0] = open("temp.txt",O_RDWR|O_CREAT|O_EXCL);
	fd[1] = open("temp.txt",O_RDWR);

	if(argc != 2){
		printf("Usage: getsections filename\n");
		return 0;
	}

	//unsigned int bfd_init(void);
	bfd *abfd;
	abfd = bfd_openr (argv[1],default_target);

	if(abfd == NULL)
	{
		printf("File not found!\n");
		return 0;
	}

	if (bfd_check_format(abfd, bfd_object))
	{
		printf("Sections:\n");
		printf("Name          VMA      Size          Position\n");
		bfd_map_over_sections(abfd, print_objdump, NULL);
	}
	else{
		printf("%c: the file is not recognized as a valid object file\n",argv[1]);
		return 0;
	}

	// if(bfd_check_format(file, bfd_archive))
	// {
	// 	bfd *last = NULL;
	// }


	
	return 0;
}
