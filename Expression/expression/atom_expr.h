#pragma once
#include "expression.h"
class atom_expr :
    public expression
{
};

class real_literal_expr :
    public atom_expr
{
    double value{};
public:
    bool is_real_literal() const override { return true; }
    real_literal_expr(double v);
    void set_value(double v) { value = v; }
    double get_value()const { return value; }

    real_literal_expr* copy() const override;
};

class variable;
class variable_expr :
    public atom_expr
{
    variable* var{};
public:
    variable_expr(variable* v);

    variable_expr* copy() const override;
    expression* calculate() const override;
};
