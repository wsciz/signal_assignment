#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t count = 0;

void handle_sigint(int sig)
{
        (void)sig;
    count++;
}

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C three times to exit.\n");

    while (count < 3)
        pause();

    printf("Received Ctrl+C three times. Exiting.\n");

    return 0;
}