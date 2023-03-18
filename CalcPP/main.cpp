#include <iostream>
#include "driver.hpp"

int main()
{
    driver* drv = new driver;
    drv->parse_file("code.txt");
    delete drv;
}
