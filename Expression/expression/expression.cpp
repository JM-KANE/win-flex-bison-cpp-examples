#include "expression.h"

expression* expression::calculate() const
{
    return copy();
}
