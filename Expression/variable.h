#pragma once

#include <string>
#include "expression/expression.h"

class variable :public object
{
private:
    std::string name_;
    expression* value_{};

public:
    template <typename T>
    variable(T&& n, expression* expr = nullptr)
        :name_(std::forward<T>(n)), value_{ expr }
    {
    }
    ~variable();

    auto value() const { return value_; }
    void set_value(expression* expr) { value_ = expr; }
    auto& name() const { return name_; }
};

