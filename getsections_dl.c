#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <stdint.h>
#include <unistd.h>
#include "objsect.h"

static char *nextln = "\n";

#define RDTSC(var)                                              \
  {                                                             \
    uint64_t var##_lo, var##_hi;                                \
    asm volatile("lfence\n\trdtsc" : "=a"(var##_lo), "=d"(var##_hi));     \
    var = var##_hi;                                             \
    var <<= 32;                                                 \
    var |= var##_lo;                                            \
  }

unsigned long long start, finish;

void run_stats(int flagn){
	float total = 0;
	void *handle;
	int i = 0;
	char *fname = "stats";
	char *flag = (flagn==0x1)? "RDTL_LAZY" :"RDTL_NOW";
	int fd = open(fname, O_RDWR|O_CREAT|O_EXCL);
	write(fd,"getsections_dl.c | ", 20);
	write(fd,flag, strlen(flag));
	write(1,nextln, strlen(nextln));
	do
	{
		RDTSC(start);
		handle = dlopen("libobjdata.so",flagn);
		RDTSC(finish);
		//cpu MHz		: 2599.994
		total += ((finish-start)/2599.994);
		i++;
	} while (i<50);

	write(fd,"Avgtime: ",10);
	char *tempavg = malloc(16*sizeof(char));
	gcvt(total/50, 5, tempavg);
	write(fd, tempavg,strlen(tempavg));
	write(1,nextln, strlen(nextln));
}

int main(int argc, char **argv){

	if(argc != 3){
		char *instruct = "Usage: getsections filename flag\n";
		// printf("Usage: getsections filename\n");
		write(1,instruct,strlen(instruct));
		write(1,nextln,strlen(nextln));
		return 0;
	}
	void *handle;
	const char *flag = argv[2];
	// //set flagn to 0x1, which is RTLC_LAZY; 0x2 for NOW
	int flagn = 0x1;
	if(strcmp(flag,"RTLD_LAZY")!= 0){flagn = 0x2;}

	RDTSC(start);
	handle = dlopen("libobjdata.so",flagn);
	RDTSC(finish);
	//cpu MHz		: 2599.994
	float time = ((finish-start)/2599.994);

	run_stats(flagn);

	if(enter_objsect(argv[1])){
		write(1,"PASS",5);
		write(1,nextln,strlen(nextln));
	}else{
		write(1,"FAIL",5);
		write(1,nextln,strlen(nextln));
	}
	
	return 0;
}
