#include  "driver.hpp"
#include <string>

int main()
{
    driver* drv = new driver;
    if (!drv->parse_file("code.txt"))
    {
        drv->calc();
    }
    /*if (!drv->parse_string("3"))
    {
        drv->calc();
    }*/

    delete drv;
    return 0;
}