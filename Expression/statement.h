#pragma once

#include "variable.h"
#include "expression/head.h"
class statement :public object
{
private:
    variable* var{};
    expression* value{};

public:
    statement(variable* v, expression* e);
    ~statement();

    auto get_variable() const { return var; }
    auto get_expression() const { return value; }

    void calc() const;
};

