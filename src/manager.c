#include "common.h"

int main() {
	pid_t my_pid, my_ppid;
	pid_t child;

	switch (fork()) {

	    case -1:
			/* Handle error */
			print_error(errno);
			break;
			
		case 0:
			/* Perform actions specific to child */
			my_pid = getpid();
			my_ppid = getppid();
			child = getpid();
			printf("CHILD:  PID=%d, PPID=%d\n", my_pid, my_ppid);
			break;
			
		default:
			/* Perform actions specific to parent */
			my_pid = getpid();
			my_ppid = getppid();
			printf("PARENT: PID=%d, PPID=%d", my_pid, my_ppid);
			printf("\nwaiting for child\n");
			wait(&child);
            printf("\nchild ended work\n");
			break;
		}
		/* Both child and parent process will execute here!! */

		printf("COMMON AREA PID: %d\n", getpid());

		exit(EXIT_SUCCESS);
}
