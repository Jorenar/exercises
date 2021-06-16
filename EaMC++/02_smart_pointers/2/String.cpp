#include "String.hpp"

String::String(size_t size) : text(new std::string(size, 'x')) {}

String::String(const char* str) : text(new std::string(str)) {}

String::String(const String& obj) : text(obj.text) {}

String String::operator =(const String& obj)
{
    if (this != &obj) {
        this->text = obj.text;
    }
    return *this;
}

char& String::operator [](int i)
{
    if (!text.unique()) {
        text.reset(new std::string(*text));
    }
    return (*text)[i];
}

char String::operator [](int i) const
{
    return (*text)[i];
}

String operator +(String a, String b)
{
    return String((*(a.text) + *(b.text)).c_str());
}

std::ostream& operator<< (std::ostream& out, String s)
{
    return out << *(s.text);
}

// vim: fen
