#pragma once

#include <map>
#include <string>
#include "scanner.hpp"

class Node
{
public:
    static int C;   // created
    static int D;   // destroyed

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

    yy::scanner* lexer{};
    yy::parser* parser{};
    bool trace_parsing{};
    bool trace_scanning{};
    yy::location location;

    driver() = default;
    ~driver();
    int parse_stream(std::istream& in);
    int parse_file(const std::string& f);
    int parse_string(const std::string& str);
};

