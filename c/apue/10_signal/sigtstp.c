/*
 *更新时间: < 修改人[liyunteng] 2014/10/27 10:59:53 >
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define BUFFSIZE	1024

 static void sig_tstp(int);

 int main(int argc, char *argv[])
 {
	 int n;
	 char buf[BUFFSIZE];

	 if (signal(SIGTSTP, SIG_IGN) == SIG_DFL)
		 signal(SIGTSTP, sig_tstp);

	 while ((n=read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		 if (write(STDOUT_FILENO, buf, n) != n)
			 fprintf(stderr, "write error");

	 if (n < 0)
		 fprintf(stderr, "read error");
	 return 0;
 }

 static void sig_tstp(int signo)
 {
	 sigset_t mask;
	 
	 sigemptyset(&mask);
	 sigprocmask(SIG_UNBLOCK, &mask, NULL);


	 signal(SIGTSTP, SIG_DFL);

	 kill(getpid(), SIGTSTP);

	 signal(SIGTSTP, sig_tstp);
}
