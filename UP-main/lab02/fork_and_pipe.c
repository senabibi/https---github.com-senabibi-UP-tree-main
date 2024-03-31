// C program to demonstrate use of fork() and pipe()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	// We use two pipes
	// First pipe to send input string from parent
	// Second pipe to send concatenated string from child

	int fd1[2]; // Used to store two ends of first pipe
	
	char input_str[100];
	pid_t p;

	if (pipe(fd1) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}

	scanf("%s", input_str);
	p = fork();

	if (p < 0) {
		fprintf(stderr, "fork Failed");
		return 1;
	}

	// Parent process
	else if (p > 0) {
		char concat_str[100];

		close(fd1[0]); // Close reading end of first pipe

		// Write input string and close writing end of first
		// pipe.
		write(fd1[1], input_str, strlen(input_str) + 1);
		close(fd1[1]);

		// Wait for child to send a string
		wait(NULL);
	
	}

	// child process
	else {
		close(fd1[1]); // Close writing end of first pipe

		// Read a string using first pipe
		char concat_str[100];
		read(fd1[0], concat_str, 100);

		close(fd1[0]);
		
		printf("Concatenated string %s\n", concat_str);

		exit(0);
	}
}
