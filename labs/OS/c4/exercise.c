#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SLEEP_TIME 5

int main()
{
    fputs("Letter of example: ", stdout);
    char c = fgetc(stdin);

    switch (c) {
        case 'a':
            for (int i = 0; i < 5; ++i) {
                if (fork()) {
                    sleep(SLEEP_TIME);
                    exit(0);
                }
            }
            break;
        case 'b':
            if (fork()) {
                if (fork()) {
                    fork();
                }
            }
            fork();
            sleep(SLEEP_TIME);
            break;
        case 'c':
            if (fork() + fork()) {
                fork();
            }
            sleep(SLEEP_TIME);
            wait(NULL);
            break;
        case 'd':
            fork();
            if (fork()) {
                sleep(SLEEP_TIME);
                wait(NULL);
            }
            break;
        case 'e':
            if (fork() * fork() * fork()) {
                fork();
            }
            sleep(SLEEP_TIME);
            wait(NULL);
            break;
        case 'f':
            for (int i = 0; i < 5; ++i) {
                int p = fork();
                if (p) {
                    kill(p, 9);
                }
                sleep(SLEEP_TIME);
            }
            break;
        case 'g':
            if (fork() < fork()) {
                fork();
            }
            sleep(SLEEP_TIME);
            break;
        case 'h':
            if (fork() <= fork()) {
                fork();
            }
            sleep(SLEEP_TIME);
            break;
    }

    return 0;
}

// vim: fen fdl=2
