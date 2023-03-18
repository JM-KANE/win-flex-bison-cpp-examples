#include "driver.hpp"
#include <fstream>
#include <sstream>

driver::~driver()
{
    delete lexer;
    delete parser;
    for (auto& stmt : statements)
    {
        delete stmt;
    }
    for (auto& var : variables)
    {
        delete var.second;
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

    // begin parse
    try
    {
        return (*parser)();
    }
    catch (const parse_error&)
    {
        return 1;
    }
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

variable* driver::lookup(const std::string& name) const
{
    if (variables.count(name))
    {
        return variables.at(name);
    }
    return nullptr;
}

void driver::add_stmt(statement* stmt)
{
    statements.emplace_back(stmt);
}

bool driver::add_variable(variable* var)
{
    if (variables.count(var->name()))
    {
        return false;
    }
    variables.emplace(var->name(), var);
    return true;
}

void driver::calc()
{
    for (auto stmt : statements)
    {
        stmt->calc();
        delete stmt;
    }
    statements.clear();

    auto res = result->calculate();
    delete result;
    result = res;
}
