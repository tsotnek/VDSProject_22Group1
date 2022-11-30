#include "Tests.h"

class managerTest : public ::testing::Test 
{
    protected:
        ClassProject::Manager testObj;
        ClassProject::BDD_ID a, b, c, d;

        void SetUp() override {
            a = testObj.createVar("a");
            b = testObj.createVar("b");
            c = testObj.createVar("c");
            d = testObj.createVar("d");
        }

        ClassProject::BDD_ID runExpression()
        {
            return testObj.and2(testObj.and2(c,d),testObj.or2(a,b));
        }
};      

TEST_F(managerTest, constructorTest)
{
    ASSERT_EQ(testObj.uniqueTable[testObj.False()].label, "False") << "Unique table does not contain false on construction";
    ASSERT_EQ(testObj.uniqueTable[testObj.True()].label, "True") << "Unique table does not contain true on construction";
}

TEST_F(managerTest, createVarTest)
{
    ClassProject::BDD_ID testVar = testObj.createVar("testVar");
    ASSERT_EQ(testObj.uniqueTable[testVar].label, "testVar") << "Incorrect creation of variable";
}

TEST_F(managerTest, uniqueTableSizeTest)
{
    size_t preSize = testObj.uniqueTableSize();
    ClassProject::BDD_ID testVar = testObj.createVar("testVar");
    ASSERT_EQ(testObj.uniqueTableSize(), preSize + 1) << "Incorrect assertion for size";
}

TEST_F(managerTest, isConstantTest)
{
    for (ClassProject::BDD_ID i = 0; i < testObj.uniqueTableSize(); i++) 
    {
        bool res = (i == testObj.False() || i == testObj.True());
        ASSERT_EQ(testObj.isConstant(i), res) << "Incorrect assertion for isConstant";
    }
}

TEST_F(managerTest, isVariableTest)
{
    runExpression();
    ClassProject::BDD_ID i = 0;
    for (auto item : testObj.uniqueTable)
    {
        bool res = (item.label == "a" || item.label == "c" || item.label == "b" || item.label == "d");
        ASSERT_EQ(testObj.isVariable(i++), res) << "Incorrect assertion for isVariable";
    }
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}