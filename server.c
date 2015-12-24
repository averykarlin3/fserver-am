#include "fserver.h"

void error(int r) {
	if(!r) {
		printf("Error: %s", strerror(errno));
	}
}

void connect() {
	char* wkp = "connect";
	int test = mkfifo(wkp, 0666);
	error(test);
	int pipe = open(wkp, O_RDWR);
	error(pipe);
	printf("WKP Created\n");
	char buffer[100];
	test = read(pipe, buffer, 100 * sizeof(char)); 
	error(test);
	printf("WKP Connection Formed\n");
	printf("Private pipe name: %s\n", buffer);
	test = close(pipe);
	error(test);
	pipe = open(buffer, O_RDWR);
	printf("Private Pipe Connection Formed\n");
}

int main() {
	
	return 0;
}
