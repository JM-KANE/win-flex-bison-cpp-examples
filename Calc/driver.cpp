#include "driver.hpp"

int Node::C{};
int Node::D{};

driver::driver()
{
}

driver::~driver()
{
    for (auto& p : variables)
    {
        delete p.second.value;
    }
    delete result;
}

int driver::parse(const std::string& f)
{
    file = f;
    location.initialize(&file);
    scan_begin();
    yy::parser _parse(*this);
    _parse.set_debug_level(trace_parsing);
    int res = _parse();
    scan_end();
    return res;
}
