#pragma once
#include "atom_expr.h"
#include <math.h>

class binary_expr :
    public expression
{
protected:
    expression* left{};
    expression* right{};
public:
    ~binary_expr();
    binary_expr(expression* lhs, expression* rhs);
    binary_expr(const binary_expr& node);
};

class numeric_expr :
    public binary_expr
{
protected:
    template<typename T>
    expression* calc_bin() const;

public:
    numeric_expr(expression* lhs, expression* rhs);

};
class pow_expr :
    public numeric_expr
{
public:
    pow_expr(expression* lhs, expression* rhs);
    pow_expr* copy() const override;
    expression* calculate() const override;
    static double calc(double lhs, double rhs) { return pow(lhs, rhs); }
};
class multi_expr :
    public numeric_expr
{
public:
    multi_expr(expression* lhs, expression* rhs);
    multi_expr* copy() const override;
    expression* calculate() const override;
    static double calc(double lhs, double rhs) { return lhs * rhs; }

};
class div_expr :
    public numeric_expr
{
public:
    div_expr(expression* lhs, expression* rhs);
    div_expr* copy() const override;
    expression* calculate() const override;
    static double calc(double lhs, double rhs) { return lhs / rhs; }
};
class add_expr :
    public numeric_expr
{
public:
    add_expr(expression* lhs, expression* rhs);
    add_expr* copy() const override;
    expression* calculate() const override;
    static double calc(double lhs, double rhs) { return lhs + rhs; }
};
class sub_expr :
    public numeric_expr
{
public:
    sub_expr(expression* lhs, expression* rhs);
    sub_expr* copy() const override;
    expression* calculate() const override;
    static double calc(double lhs, double rhs) { return lhs - rhs; }
};

template<typename T>
inline expression* numeric_expr::calc_bin() const
{
    auto resL = left->calculate();
    auto resR = right->calculate();
    if (resL->is_real_literal() && resR->is_real_literal())
    {
        auto litL = static_cast<real_literal_expr*>(resL);
        auto litR = static_cast<real_literal_expr*>(resR);
        auto dRes = T::calc(litL->get_value(), litR->get_value());
        delete litL;
        delete litR;
        return new real_literal_expr(dRes);
    }
    else
    {
        return new T(resL, resR);
    }
}
