#include "lib.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    lib::print_ip(char(-1), std::cout);
    lib::print_ip(short(0), std::cout);
    lib::print_ip(int(2130706433), std::cout);
    lib::print_ip(long(8875824491850138409), std::cout);


    // lib::print_ip(std::vector<int>({1,2,3}), std::cout);

    lib::print_ip(std::string("1.2.3.4.5"), std::cout);

    return 0;
}
