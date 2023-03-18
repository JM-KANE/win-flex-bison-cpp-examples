#include <iostream>
#include "driver.hpp"

int main()
{
    driver* drv = new driver;
    drv->parse("code.txt");
    delete drv;
}
