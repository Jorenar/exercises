#ifndef LZW_HPP_
#define LZW_HPP_

#include <string>
#include <cstdint>

#include "LinkedList.hpp"

namespace lzw {

List<uint16_t> encode(std::string);
std::string decode(List<uint16_t>&);

void write(std::ostream&, List<uint16_t>&);
List<uint16_t> read(std::istream&);

} // namespace lzw

#endif // LZW_HPP_
