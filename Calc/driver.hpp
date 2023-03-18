#pragma once

#include <map>
#include <string>
#include "parser.hpp"

#define YY_DECL yy::parser::symbol_type yylex (driver& drv)

YY_DECL;

class Node
{
public:
    static int C;
    static int D;

    int value{};

    Node(int v) :value{ v } { C++; }
    ~Node()
    {
        D++;
    }

    auto Copy() const
    {
        C++;
        return new auto(*this);
    }
};

class driver
{
public:
    struct VariableInfo
    {
        yy::location loc;
        Node* value{};
    };

    std::map<std::string, VariableInfo> variables;
    Node* result{};
    std::string file;
    bool trace_parsing{};
    bool trace_scanning{};
    yy::location location;

    driver();
    ~driver();
    int parse(const std::string& f);

    // Handling the scanner.
    void scan_begin();
    void scan_end();
};

