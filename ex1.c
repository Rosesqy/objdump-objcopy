#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void itoa(int n, char * str)
{
	int len = 0;
	int m = n, i;
	while (m != 0) {
		m = m / 10;
		len++;
	}

	for (i = len - 1; i >= 0; i--) {
		str[i] = n % 10 + '0';
		n = n / 10;
	}

	str[len] = 0;
}

int main(int argc, char** argv){
    if (argc < 3){
        printf("Usage: ex1 filename number\n");
        return 0;
    }
    
    int num1, num2;
    char buffer[512];
    char result[512];
    memset(result, 0, 512);
    size_t bytes_read;
    // Get the num1 from the command line
    num1 = strtol(argv[2], NULL, 10);
    // Open the file as Read/Write
    FILE *fp = fopen(argv[1], "r");
    // Read up to 512 bytes from the file
    bytes_read = fread(buffer, sizeof(char), 512, fp);
    // Get num2 from the file
    num2 = strtol(buffer, NULL, 10);
    fclose(fp);
    // Sum the two numbers and write the results back
    itoa(num1+num2, result);
    printf("num1 = %d, num2 = %d, sum = %s\n", num1, num2, result);
    
    fp = fopen(argv[1], "w");
    fwrite(result, sizeof(char), 512, fp);
    
    // Wait for a keystroke and then close the file
    char c = getc(stdin);
    fclose(fp);
    return 0;
}
