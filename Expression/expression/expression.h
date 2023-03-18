#pragma once

#include "../object.h"
class expression :public object
{
public:
    virtual expression* calculate() const;
    virtual expression* copy() const = 0;

    virtual bool is_real_literal() const { return false; }
};

