#include "variable.h"

variable::~variable()
{
    delete value_;
}
