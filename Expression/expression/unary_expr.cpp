#include "unary_expr.h"
#include "atom_expr.h"

unary_expr::unary_expr(expression* e) :expr{ e }
{
}

unary_expr::unary_expr(const unary_expr& node) :expr{ node.expr->copy() }
{
}

unary_expr::~unary_expr()
{
    delete expr;
}

neg_expr* neg_expr::copy() const
{
    return new auto(*this);
}

expression* neg_expr::calculate() const
{
    auto res = expr->calculate();
    if (res->is_real_literal())
    {
        auto literal = static_cast<real_literal_expr*>(res);
        literal->set_value(-literal->get_value());
    }
    else
    {
        res = new neg_expr(res);
    }
    return res;
}

neg_expr::neg_expr(expression* e) :unary_expr{ e }
{
}
