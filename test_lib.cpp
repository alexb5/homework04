#include "lib.h"

#include <gtest/gtest.h>

TEST(version_test_case, version_test)
{
    EXPECT_GT(lib::version_patch(), 0);
    EXPECT_GT(lib::version_major(), 0);
    EXPECT_GT(lib::version_minor(), 0);
}