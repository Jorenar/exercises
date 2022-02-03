#ifndef MACROS_H_
#define MACROS_H_

#define NL printf("\n")

#ifdef __unix__
    #define RESET       "\033[0m"
    #define BOLD        "\033[1m"
    #define RED         "\033[31m"
    #define BOLD_NR "\033[1m%d\033[0m"
#else
    #define RESET       ""
    #define BOLD        ""
    #define RED         ""
    #define BOLD_NR "%d"
#endif

#endif
