#include "atom_expr.h"

real_literal_expr::real_literal_expr(double v) :value{ v }
{
}

real_literal_expr* real_literal_expr::copy() const
{
    return new real_literal_expr(*this);
}

#include "../variable.h"
variable_expr::variable_expr(variable* v) :var{ v }
{
}

variable_expr* variable_expr::copy() const
{
    return new variable_expr(*this);
}

expression* variable_expr::calculate() const
{
    if (!var->value())
    {
        return copy();
    }

    auto value = var->value();
    auto res = value->calculate();
    delete value;
    var->set_value(res->copy());
    return res;
}

