#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUMSIGS 64

void (sig_handler) (int);

int sig_count[NUMSIGS+1];
volatile static int line = 0;
volatile int signumbuffer[6400];

int main(int argc, char *argv[])
{
	sigset_t newmask, oldmask;
	struct sigaction sigact, oldact;
	int signum, rc, i;

	// Block all signals
	rc = sigfillset(&newmask);
	rc = sigprocmask(SIG_SETMASK, &newmask, &oldmask);

	memset(&sigact, 0, sizeof(struct sigaction));
	sigact.sa_handler = sig_handler; // Pointer to sig handler
	sigact.sa_flags = 0; // No flags
	sigact.sa_mask = newmask; // Block signals inside the handler

	// Initialize signals
	for(signum = 1; signum <= NUMSIGS; signum++)
	{
		if (signum == SIGKILL || signum == SIGSTOP 
				|| signum == 32 || signum == 33)
		{
			continue;
		}
		sigaction(signum, &sigact, &oldact);
	}
	
	// Send all signals multiple times
	for (signum = 1; signum <= NUMSIGS; signum++)
	{
		if (signum == SIGKILL || signum == SIGSTOP
				|| signum == 32 || signum == 33)
		{
			continue;
		}
		for (i = 0; i < 3; i++)
		{
			rc = raise(signum);
			if (rc)
			{
				printf("Failed on signal: %d\n", signum);
			}
			else
			{
				printf("Raised signal: %d\n", signum);
			}
		}
	}
	
	// Restore signalmask
	rc = sigprocmask(SIG_SETMASK, &oldmask, NULL);

	// Print results
	for (i = 1; i <= NUMSIGS; i++)
	{
		printf("Signal %d processed %d times\n", i, sig_count[i]);
	}
	for (i = 0; i < line; i++)
	{
		if (i % 15 == 0)
		{
			printf("\n");
		}
		printf("%d ", signumbuffer[i]);
	}
	printf("\n");
	return 0;
}

void sig_handler(int sig)
{
	sig_count[sig]++;
	signumbuffer[line] = sig;
	line++;
}

