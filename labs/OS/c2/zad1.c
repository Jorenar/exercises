#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// I've assumed, files "stdout.txt" and "stderr.txt" are to be yet created.

void validate(int id)
{
    if (id == -1) {
        printf("Couldn't open file (err = %d)\n", errno);
        exit(errno);
    }
}

int main()
{
    // Preparing streams {{{
    int in = open("stdin.txt", O_RDONLY);
    validate(in);

    int out = creat("stdout.txt", 0640);
    validate(out);

    int err = creat("stderr.txt", 0640);
    validate(err);

    dup2(in,  0);
    dup2(out, 1);
    dup2(err, 2);
    // END: preparing streams }}}

    char tab[20];

    read(0, tab, 20);
    write(1, tab, 20);
    fprintf(stderr, "Komunikat");

    close(in);
    close(out);
    close(err);

    return 0;
}
