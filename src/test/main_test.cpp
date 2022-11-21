//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
#include "../Manager.h"
#include "../ManagerInterface.h"


TEST(myTests, test1) {
        ClassProject::Manager* myTest;
        ASSERT_EQ(myTest->a, 1) << "a is not 1";
    }

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);


    return RUN_ALL_TESTS();
}
