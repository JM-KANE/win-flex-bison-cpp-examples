#include "driver.hpp"
#include <fstream>
#include <sstream>

int Node::C{};
int Node::D{};

driver::~driver()
{
    delete lexer;
    delete parser;
    for (auto& p : variables)
    {
        delete p.second.value;
    }
    delete result;
}

int driver::parse_stream(std::istream& in)
{
    if (lexer)
    {
        delete lexer;
    }
    lexer = new yy::scanner(in);
    lexer->set_debug(trace_scanning);
    if (parser)
    {
        delete parser;
    }
    parser = new yy::parser(*this);
    parser->set_debug_level(trace_scanning);
    return (*parser)();
}

int driver::parse_file(const std::string& f)
{
    std::ifstream in(f);
    if (!in)
    {
        return 1;
    }
    auto res = parse_stream(in);
    in.close();
    return res;
}

int driver::parse_string(const std::string& str)
{
    std::istringstream iss(str);
    return parse_stream(iss);
}
