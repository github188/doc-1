#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

#define  MAX (10)

int glob = 5;
char buf[] = "a write to stdout\n";

int main(int argc, char *argv[])
{
	int var;
	pid_t pid;

	var = 88;
	MAX;

        if ( write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1) {
		fprintf(stderr,"write error!\n");
	}
	printf("before fork!\n");

	if ((pid=fork()) < 0) {
		fprintf(stderr,"fork failed.\n1");
		return -1;
	} else if (pid == 0) {
		glob ++;
		var ++;
	} else {
		waitpid(pid, NULL, NULL);
	}

	printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var); 
	return 0;


}
