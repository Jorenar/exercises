#include <fstream>
#include <iostream>

#include <getopt.h>

#include "lzw.hpp"

void usage()
{
    std::cout <<
        "Usage: lzm [-dh] [-f path] [-o path]\n"
        "  -f  read from file instead of stdin\n"
        "  -o  write to file instead of stdout\n"
        "  -d  decompression is done instead\n"
        "  -h  prints this help message\n"
        "";
}

int main(int argc, char* argv[])
{
    bool decompress = false;
    const char* input_file = NULL;
    const char* output_file = NULL;

    int opt;
    while ((opt = getopt(argc, argv, ":f:o:dh")) != -1) {
        switch (opt) {
            case 'f':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'd':
                decompress = true;
                break;
            case 'h':
                usage();
                return 0;
                break;
            case ':':
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                usage();
                return 1;
                break;
        }
    }

    if (optind < argc) {
        printf("unknown argument: %s\n", argv[optind]);
        usage();
        return 1;
    }

    std::ifstream fi;
    std::ofstream fo;

    std::istream& in = input_file ? (fi.open(input_file, std::ios::binary), fi) : std::cin;
    std::ostream& out = output_file ? (fo.open(output_file, std::ios::binary), fo) : std::cout;

    if (!decompress) {
        std::string data((std::istreambuf_iterator<char>(in)),
                         (std::istreambuf_iterator<char>()));
        auto&& output_code = lzw::encode(data);
        lzw::write(out, output_code);
    }
    else {
        auto&& input_code = lzw::read(in);
        out << lzw::decode(input_code);
    }

    return 0;
}
