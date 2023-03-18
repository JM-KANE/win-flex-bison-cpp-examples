#include "binary_expr.h"

binary_expr::~binary_expr()
{
    delete left;
    delete right;
}

binary_expr::binary_expr(expression* lhs, expression* rhs)
    :left{ lhs }, right{ rhs }
{
}

binary_expr::binary_expr(const binary_expr& node)
    :left{ node.left->copy() }, right{ node.right->copy() }
{
}

pow_expr::pow_expr(expression* lhs, expression* rhs)
    :numeric_expr{ lhs ,rhs }
{
}

#define MAKE_COPY_CALC(T) T##_expr* T##_expr::copy() const \
    { return new auto(*this); } \
    expression* T##_expr::calculate() const \
    { return calc_bin<T##_expr>(); }

MAKE_COPY_CALC(pow)
MAKE_COPY_CALC(multi)
MAKE_COPY_CALC(div)
MAKE_COPY_CALC(add)
MAKE_COPY_CALC(sub)

multi_expr::multi_expr(expression* lhs, expression* rhs)
    :numeric_expr{ lhs ,rhs }
{
}

div_expr::div_expr(expression* lhs, expression* rhs)
    :numeric_expr{ lhs ,rhs }
{
}

add_expr::add_expr(expression* lhs, expression* rhs)
    :numeric_expr{ lhs ,rhs }
{
}

sub_expr::sub_expr(expression* lhs, expression* rhs)
    :numeric_expr{ lhs ,rhs }
{
}

numeric_expr::numeric_expr(expression* lhs, expression* rhs)
    :binary_expr(lhs, rhs)
{
}
