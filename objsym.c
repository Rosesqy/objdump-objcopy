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
        char *stringnow = malloc(strlen(temp));
        
        while(val){
        	stringnow[i++] = base[val%16];
       		val /= 16;}
                                                                     
        stringnow[i] = '\0';
        //                                                                        //write(1,stringnow,strlen(stringnow));
        //
        //                                                                                int j = 0;
        //                                                                                        //fill the terminator firstly
        //                                                                                                temp[i] = '\0';
        //                                                                                                        while(j<i){
        //                                                                                                                        temp[j] = stringnow[i-1-j];
        //                                                                                                                                        j++;
        //                                                                                                                                                }
        //
        //                                                                                                                                                        return temp;
}

void print_nm(bfd *abfd){

	//const char *namep;
	//initialize a temp charset for later use
	char temp[16] = {0};

	//get the number of bytes required to store a vector of pointers to asymbols for all the symbols in the BFD abfd, including a terminal NULL pointer. If there are no symbols in the BFD, then return 0. If an error occurs, return -1.
	size_t storesize = bfd_get_symtab_upper_bound(abfd);
	//deal with error
	if(storesize < 0){
		bfd_perror(NULL);
		return;
	}
	//pointer to pointers to symbols
	asymbol **symptrs;
	//create a space to save the pointer to pointers
	symptrs = malloc(storesize);
	//Read the symbols from the BFD abfd, and fills in the vector location with pointers to the symbols and a trailing NULL. Return the actual number of symbol pointers, not including the NULL.
	int symptrsnum = bfd_canonicalize_symtab(abfd, symptrs);
	//deal with error
	if(symptrsnum < 0){
		bfd_perror(NULL);
		return;
	}
	int i;
	//for each symbol, print name and vma. "Each line of the output should print a single symbol name and the corresponding virtual memory address" 
	//when calculate symbol vma, we need the vma of section it points to and, the value of the symbol, which is the amount of space the symbol requires
	for(i = 0; i < symptrsnum; i++){
		const char *sname = symptrs[i]->name;
		write(1,sname, strlen(sname));
		write(1,sep,strlen(sep));
		char temp[16] = {0};
		char *svma = long_to_string(symptrs[i]->section->vma+symptrs[i]->value,temp);
		write(1,svma, strlen(svma));
		write(1,nextln,strlen(nextln));
	}
}

bool enter_objsym(char *inputf){
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
		print_nm(abfd);
	}
	else{
		char *nobject = ": the file is not recognized as a valid object file\n";
		write(1,inputf,strlen(inputf));
		write(1,nobject,strlen(nobject));
		return false;
	}
	return true;
}

