//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
#include "../Manager.h"
#include "../ManagerInterface.h"


TEST(managerTests, constructorTest)
{
    ClassProject::Manager* testObj = new ClassProject::Manager();
    ASSERT_EQ(testObj->uniqueTable[0].high, 0) << "Unique table does not contain false on construction";
    ASSERT_EQ(testObj->uniqueTable[1].low, 1) << "Unique table does not contain true on construction";
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);


    return RUN_ALL_TESTS();
}
