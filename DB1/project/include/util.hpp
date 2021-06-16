#pragma once

#include <string>

/// Code of combination of CTRL and other key
#define CTRL(x)  ((x) & 0x1F)

char getch();
int winRows();
std::string uCharToStr(const unsigned char* s);
void clear();
std::string Readline(const std::string& prompt, const std::string& def);
