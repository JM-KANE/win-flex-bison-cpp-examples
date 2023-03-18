#pragma once
class object
{
public:
    static size_t constructed;
    static size_t destructed;

    object();
    object(const object&);
    virtual ~object();
};

