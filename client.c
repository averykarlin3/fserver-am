#include "fserver.h"

void error(int r) {
	if(!r) {
		printf("Error: %s", strerror(errno));
	}
}

void connect() {
	char* wkp = "connect";
	char* private = ftok("fserver.h", 2016);
	pipe = open(wkp, O_RDWR);
	error(pipe);
	printf("WKP Connection Formed\n");
	int test = mkfifo(private, 0666);
	error(test);
	printf("Private Pipe Created\n");
	test = write(pipe, private, sizeof(private));	
	error(test);
	test = close(pipe);
}

int main() {
	
	return 0;
}
