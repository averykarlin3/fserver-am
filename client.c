#include "fserver.h"

void error(int r) {
	if(r < 0) {
		printf("Error: %s\n", strerror(errno));
	}
}

void connect() {
	char* wkp = "connect";
	char* private;
	sprintf(private, "%i", getpid());
	int from = open(wkp, O_WRONLY);
	error(from);
	printf("<C> Connected to WKP\n");
	int test = write(from, private, sizeof(private));
	error(test);
	test = mkfifo(private, 0666);
	error(test);
	int to = open(private, O_RDONLY);
	printf("<C> Connected to Private\n");
	error(to);
	char buffer[100];
	test = read(to, buffer, sizeof(buffer));	
	printf("%s\n", buffer);
	error(test);
	remove(private);
}

int main() {
	connect();
	return 0;
}
