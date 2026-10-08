#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t count = 0;
volatile sig_atomic_t interval = 0;
volatile sig_atomic_t repeat = 0;

void handle_sigalrm(int sig)
{
    (void)sig;
    count++;

    if (count < repeat)
        alarm(interval);
}

int main(int argc, char *argv[])
{
    struct sigaction sa;

    if (argc != 3)
    {
        printf("Usage: %s <interval> <repeat>\n", argv[0]);
        return 1;
    }

    interval = atoi(argv[1]);
    repeat = atoi(argv[2]);

    sa.sa_handler = handle_sigalrm;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGALRM, &sa, NULL);

    alarm(interval);

    while (count < repeat)
        pause();

    printf("Timer finished: %d times\n", count);

    return 0;
}