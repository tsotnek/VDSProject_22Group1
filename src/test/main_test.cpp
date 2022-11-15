//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    TEST(myTests, test1) {
        ASSERT_EQ(myTest(), 5) << "myTest does not return 5";
    }

    return RUN_ALL_TESTS();
}
