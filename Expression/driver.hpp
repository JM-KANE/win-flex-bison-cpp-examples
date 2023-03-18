#pragma once
#include "statement.h"
#include "scanner.hpp"
#include <vector>
#include <map>

namespace yy
{
    class scanner;
    class parser;
}

class driver
{
    friend yy::scanner;
    friend yy::parser;
private:
    std::vector<statement*> statements;
    std::map<std::string, variable*> variables;
    expression* result{};

    yy::scanner* lexer{};
    yy::parser* parser{};
    bool trace_parsing{};
    bool trace_scanning{};
    yy::location location;

public:
    struct parse_error :std::exception {};

    driver() = default;
    ~driver();
    int parse_stream(std::istream& in);
    int parse_file(const std::string& f);
    int parse_string(const std::string& str);

    variable* lookup(const std::string& name) const;
    void add_stmt(statement* stmt);
    bool add_variable(variable* var);

    void calc();
};


