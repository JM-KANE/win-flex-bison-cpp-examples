#include "Scanner.hpp"

#include <sstream>

int main()
{
    std::istringstream s("12");
    std::ostringstream s2;
    //auto& s2 = std::cerr;

    auto scanner = new Scanner(s, s2);
    scanner->lex();
    delete scanner;
}