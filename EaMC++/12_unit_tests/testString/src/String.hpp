#pragma once

#include <memory>
#include <ostream>
#include <string>

class String {
  public:
    String(size_t size = 0);  // creates an empty string
    String(const char* str);  // copy C-string
    String(const String&);   // no copy
    String operator =(const String&);  // no copy
    char& operator [](int i);
    char operator [](int i) const;
    friend String operator +(String a, String b);
    friend std::ostream& operator <<(std::ostream& out, String s);

  private:
    std::shared_ptr<std::string> text;
};
