#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Printer {
  public:
    Printer(ostream& out_, string start_, string end_) :
        out(out_), start(start_), end(end_) {}

    template<typename T> void operator ()(T x)
    {
        out << start << x << end;
    }

  private:
    ostream& out;
    string start;
    string end;
};

int main()
{
    Printer print(std::cout,  "[ ", " ] " );   // creates unary functor
    //that takes argument x of any type
    // and prints [ x ]
    print("hello");    // [ hello ]
    std::vector<int> v = {1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), print);  // [ 1 ] [ 2 ] [ 3 ] [ 4 ]

    std::ofstream file("myFile.txt");
    Printer filePrinter(file, "- ", "\n");
    filePrinter(5);
    filePrinter("My text");
    return 0;
}
/** myFile.txt
  - 5
  - My text
  */
