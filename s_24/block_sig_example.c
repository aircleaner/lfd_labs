#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rc;
	sigset_t sigsus, oldset;

	// Block all possible signals
	rc = sigfillset(&sigsus);
	rc = sigprocmask(SIG_SETMASK, &sigsus, &oldset);
	printf("going to sleep 5 s, try ctrl-C!\n");
	sleep(5);
	printf("going ahead\n");

	// restore original mask
	rc = sigprocmask(SIG_SETMASK, &oldset, NULL);
	
	// The program shoudl terminate before next loop if ctrl-c
	// was pressed while blocked
	
	// Do something pointless forever
	for(;;)
	{
		printf("This is a message.\n");
		sleep(1);
	}
	return 0;
}
