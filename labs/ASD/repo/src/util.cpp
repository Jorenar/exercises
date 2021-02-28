#include "util.hpp"

#ifdef __unix__
#include <cstdio>

int rnd()
{
    std::FILE* f = std::fopen("/dev/random", "r");
    unsigned int randval;
    std::fread(&randval, sizeof(randval), 1, f);
    std::fclose(f);
    return randval;
}

#else

#include <time.h>

int rnd()
{
    static int f = 1;
    if (f) {
        std::srand(std::time(NULL));
        f = 0;
    }
    return std::rand();
}

#endif
