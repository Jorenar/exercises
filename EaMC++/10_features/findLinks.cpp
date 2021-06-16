#include <iostream>
#include <regex>

namespace href {

  class url {
    public:

      static constexpr const char* pattern()
      {
          return R"#(<a.*?href="(https?:\/\/[.\w\d_-]+\.\w+.*)".*?>[\s\n]*(.+?)[\s\n]*<\/a>)#";
      }

      static void print(const std::smatch& match)
      {
          std::cout << match[2] << " : " << match[1] << std::endl;
      }

      static void title()
      {
          std::cout << "Links" << std::endl;
      }

  };

  class email {
    public:

      static constexpr const char* pattern()
      {
          return R"#([.\w\d_-]+@[.\w\d-]+\.\w+)#";
      }

      static void print(const std::smatch& match)
      {
          std::cout << " > " << match[0] << std::endl;
      }

      static void title()
      {
          std::cout << "Emails:" << std::endl;
      }

  };

  template<typename P>
  void find(std::string str)
  {
      auto flags = std::regex_constants::ECMAScript | std::regex_constants::icase;
      std::regex reg(P::pattern(), flags);
      auto match_start = std::sregex_iterator(str.begin(), str.end(), reg);
      auto match_end = std::sregex_iterator();
      P::title();
      for (auto it = match_start; it != match_end; ++it) {
          P::print(*it);
      }
      std::cout << std::endl;
  }

}

int main()
{
    std::cin >> std::noskipws;
    std::istream_iterator<char> it(std::cin);
    std::istream_iterator<char> end;
    std::string src(it, end);
    href::find<href::url>(src);
    href::find<href::email>(src);
    return 0;
}

// vim: fen fdl=2
