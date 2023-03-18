#include "statement.h"

statement::statement(variable* v, expression* e)
    :var{ v }, value{ e }
{
}

statement::~statement()
{
    delete value;
}

void statement::calc() const
{
    auto res = value->calculate();

    delete var->value();
    var->set_value(res);
}
