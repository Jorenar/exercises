#include "lzw.hpp"

#include "Dict.hpp"

List<uint16_t> lzw::encode(std::string data)
{
    Dict<std::string, uint16_t> table;
    for (uint16_t i = 0; i <= 255; ++i) {
        table[std::string{ static_cast<char>(i) }] = i;
    }

    std::string p = std::string{ data[0] };
    uint16_t code = 256;

    List<uint16_t> output_code;

    for (std::size_t i = 0; i < data.length(); ++i) {
        std::string c = "";

        if (i != data.length() - 1) {
            c += data[i+1];
        }

        if (table.find(p + c)) {
            p += c;
        }
        else {
            output_code.push_back(table[p]);
            table[p + c] = code;
            ++code;
            p = c;
        }
    }

    output_code.push_back(table[p]);
    return output_code;
}

std::string lzw::decode(List<uint16_t>& code)
{
    Dict<uint16_t, std::string> table;

    for (uint16_t i = 0; i <= 255; ++i) {
        table[i] = std::string{ static_cast<char>(i) };
    }

    auto old = code.pop_front();
    std::string s = table[old];
    std::string out = s;
    std::string c = std::string{ s[0] };
    uint16_t count = 256;

    while (!code.empty()) {
        auto n = code.pop_front();

        s = table.find(n) ? table[n] : table[old] + c;
        out += s;

        c = std::string{ s[0] };
        table[count] = table[old] + c;
        ++count;
        old = n;
    }

    return out;
}

void lzw::write(std::ostream& out, List<uint16_t>& code)
{
    auto write_byte = [&out](auto b) {
        out.write(reinterpret_cast<char*>(&b), 1);
    };

    uint8_t c;
    bool carry = false;

    while (!code.empty() || carry) {
        uint16_t x = 0;

        if (carry) {
            if (!code.empty()) {
                x = code.pop_front();
            }

            c = static_cast<uint8_t>(c | ((0xF00 & x) >> 8));
            write_byte(c);
            c = static_cast<uint8_t>(0xFF & x);
            write_byte(c);

            carry = false;
        }
        else {
            x = code.pop_front();
            c = static_cast<uint8_t>(x >> 4);
            write_byte(c);

            c = static_cast<uint8_t>((0xF & x) << 4);
            carry = true;
        }
    }
}

List<uint16_t> lzw::read(std::istream& in)
{
    List<uint16_t> out;

    char c;
    bool carry = false;

    bool discard_last = false;

    auto get_byte = [&in, &discard_last](auto& b) {
        in.get(b);
        discard_last = !discard_last;
    };

    while (in /* ugly check, but cheap ;) */) {
        uint16_t x;

        if (carry) {
            x = static_cast<uint16_t>(c << 8);
            get_byte(c);
            x |= static_cast<uint8_t>(c);
            out.push_back(x);

            carry = false;
        }
        else {
            get_byte(c);
            x = static_cast<uint16_t>(c << 4);
            get_byte(c);
            x |= ((0xF0 & c) >> 4);
            out.push_back(x);

            c &= 0xF;
            carry = true;
        }
    }

    /* fix the consequences of ugly loop condition */ {
        out.pop_back();
        discard_last = !discard_last;
    }

    if (discard_last) { // because it's just padding when odd number of bytes
        out.pop_back();
    }

    return out;
}
