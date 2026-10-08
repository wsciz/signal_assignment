#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t received = 0;

void handle_sigint(int sig)
{
    (void)sig;
    received = 1;
}

int main(void)
{
    struct sigaction sa;
    sigset_t set;
    sigset_t oldset;

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    sigprocmask(SIG_BLOCK, &set, &oldset);

    printf("SIGINT is blocked for 5 seconds.\n");
    printf("Press Ctrl+C now.\n");

    sleep(5);

    sigprocmask(SIG_SETMASK, &oldset, NULL);

    if (received)
        printf("SIGINT was received after unblocking.\n");
    else
        printf("SIGINT was not received.\n");

    return 0;
}