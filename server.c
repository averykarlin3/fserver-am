#include "fserver.h"

void error(int r) {
	if(r < 0) {
		printf("Error: %s\n", strerror(errno));
	}
}

void connect() {
	char* wkp = "connect";
	int test = mkfifo(wkp, 0666);
	error(test);
	int to = open(wkp, O_RDONLY);
	error(to);
	printf("<S> Connected to WKP\n");
	char buffer[100];
	test = read(to, buffer, sizeof(buffer)); 
	error(test);
	printf("<C> Connected to WKP\n");
	printf("Private Pipe Name: %s\n", buffer);
	remove(wkp);
	int parent = fork();
	error(parent);
	if(!parent) {
		int from = open(buffer, O_WRONLY);
		error(from);
		printf("<S> Connected to Private\n");
		char* confirm = "<S> Connected to Private\n";
		test = write(from, confirm, sizeof(confirm));
		error(test);
	}
	else {
		connect();
	}
}

int main() {
	connect();	
	return 0;
}
