#include "util.hpp"

#include <iostream>
#include <stdlib.h>

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <readline/readline.h>

char getch()
{
    char buf = '\0';
    struct termios old {};
    if (tcgetattr(0, &old) < 0) {
        perror("tcsetattr()");
    }
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) {
        perror("tcsetattr ICANON");
    }
    if (read(0, &buf, 1) < 0) {
        perror("read()");
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        perror("tcsetattr ~ICANON");
    }
    return buf;
}

int winRows()
{
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_row;
}

std::string uCharToStr(const unsigned char* s)
{
    return s ? (char*)s : "";
}

void clear()
{
    std::cout << "\033[2J\033[H";
}


static const char* deftext;

static int limit_rl(FILE* dummy)
{
    if (rl_end > 255) {
        return '\b';
    }
    return rl_getc(dummy);
}

static int set_deftext()
{
    if (deftext) {
        rl_insert_text (deftext);
        deftext = NULL;
        rl_startup_hook = NULL;
    }
    return 0;
}

std::string Readline(const std::string& prompt, const std::string& def)
{
    deftext = def.c_str();
    rl_startup_hook = set_deftext;
    rl_getc_function = limit_rl;
    char* temp = readline(prompt.c_str());
    std::string str{ temp };
    free(temp);
    return str;
}
