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

TEST(managerTests, createVarTest)
{
    ClassProject::Manager* testObj = new ClassProject::Manager();
    testObj->createVar("testVar");
    ASSERT_EQ(testObj->uniqueTable[2].id, 3) << "Did not create";
    ASSERT_EQ(testObj->uniqueTable[2].label, "testVar") << "Did not create";
}

TEST(managerTests, trivialTest)
{
    ClassProject::Manager* testObj = new ClassProject::Manager();
    testObj->createVar("testVar");
    ASSERT_EQ(testObj->uniqueTableSize(),testObj->uniqueTable.size()) << "Wrong size";
    ASSERT_EQ(testObj->True(), 2) << "Wrong id for True";
    ASSERT_EQ(testObj->False(), 1) << "Wrong id for False";
    ASSERT_EQ(testObj->isVariable(3), true) << "Not a variable";
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);


    return RUN_ALL_TESTS();
}
