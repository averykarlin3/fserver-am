#include "fserver.h"

void error(int r) {
	if(!r) {
		printf("Error: %s\n", strerror(errno));
	}
}

void connect() {
	char* wkp = "connect";
	char* private;
	sprintf(private, "%i", ftok("fserver.h", 2016));
	int pipe = open(wkp, O_RDWR);
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
	connect();	
	return 0;
}
