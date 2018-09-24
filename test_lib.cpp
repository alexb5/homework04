#include "lib.h"

#include <gtest/gtest.h>
#include <list>
#include <sstream>
#include <vector>

TEST(version_test_case, version_test)
{
    EXPECT_GT(lib::version_patch(), 0);
    EXPECT_GT(lib::version_major(), 0);
    EXPECT_GT(lib::version_minor(), 0);
}

TEST(print_ip, test_print_integral_types)
{
    std::stringstream s;
    
    lib::print_ip(uint8_t{}, s);
    lib::print_ip(char{-1}, s);
    lib::print_ip(uint8_t{1}, s);
    lib::print_ip(uint16_t{0xFEFF}, s);
    lib::print_ip(uint32_t{0xFCFDFEFF}, s);


    EXPECT_EQ(s.str(), std::string{"0\n255\n1\n255.254\n255.254.253.252\n"});
}

TEST(print_ip, test_print_container_types)
{
    std::stringstream s;
    
    lib::print_ip(std::vector<int>{1,2,3,4}, s);
    lib::print_ip(std::list{4,3,2,1}, s);

    EXPECT_EQ(s.str(), std::string{"1.2.3.4\n4.3.2.1\n"});
}

TEST(print_ip, test_print_tuple)
{
    std::stringstream s;
    
    lib::print_ip(std::make_tuple(1, 2, 3, 4), s);

    EXPECT_EQ(s.str(), std::string{"1.2.3.4\n"});
}