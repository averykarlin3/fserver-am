#include "fserver.h"

void error(int r) {
	if(r < 0) {
		printf("Error: %s\n", strerror(errno));
	}
}

int connect(int* from) {
	char* wkp = "connect";
	char private[100];
	sprintf(private, "%i", getpid());
	*from = open(wkp, O_WRONLY);
	error(*from);
	printf("<C> Connected to WKP\n");
	int test = write(*from, private, sizeof(private));
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
	return to;
}

void process(char* input, int from, int to) {
	printf("Sending: %s\n", input);
	int test = write(from, input, sizeof(input));
	error(test);
	char buffer[100];
	test = read(to, buffer, sizeof(buffer));
	error(test);
	printf("Processed: %s\n", buffer);
}

int main() {
	int from, to;
	to = connect(&from);
	while(1) {
		char input[100];
		printf("Insert Data: ");
		char* testa = fgets(input, sizeof(input), stdin);
		*strchr(input, '\n') = 0;
		//printf("Input: %s", input);
		//printf("Size of Input: %lu\n", sizeof(test));
		if (testa == NULL) {
			error(-1);
		}
		if(!strcmp(input, "exit"))
			break;
		//process(input, from, to);
		printf("Sending: %s\n", input);
		int test = write(from, input, sizeof(input));
		error(test);
		char buffer[100];
		test = read(to, buffer, sizeof(buffer));
		error(test);
		printf("Processed: %s\n", buffer);
	}
	close(from);
	close(to);
	return 0;
}
