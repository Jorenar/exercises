#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SLEEP_TIME 5

int main()
{
    // 8 zombies
    for (int i = 0; i < 8; ++i) {
        if (fork() == 0) {
            // those children will die way before their parent
            exit(0);
        }
    }

    // 7 orphans
    for (int i = 0; i < 7; ++i) {
        if (fork() == 0) {
            // double of sleep time, those children will end way past their parent death
            sleep(2 * SLEEP_TIME);
            exit(0);
        }
    }

    // 19 - (8 + 7) = 4
    for (int i = 0; i < 4; ++i) {
        if (fork() == 0) {
            // those will die together with their parent
            sleep(SLEEP_TIME);
            exit(0);
        }
    }

    sleep(SLEEP_TIME);

    return 0;
}
