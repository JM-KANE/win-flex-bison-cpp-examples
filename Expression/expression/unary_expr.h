#pragma once
#include "expression.h"
class unary_expr :
    public expression
{
protected:
    expression* expr{};
public:
    unary_expr(expression* e);
    unary_expr(const unary_expr& node);

    ~unary_expr();
};

class neg_expr :
    public unary_expr
{
public:
    neg_expr(expression* e);

    neg_expr* copy() const override;
    expression* calculate() const override;
};
