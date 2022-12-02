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
            return testObj.and2(testObj.or2(a,b),testObj.and2(c,d));
        }
};      

TEST_F(managerTest, constructorTest)
{
    ASSERT_EQ(testObj.uniqueTable[testObj.False()].label, "False") << "Unique table does not contain false on construction";
    ASSERT_EQ(testObj.uniqueTable[testObj.True()].label, "True") << "Unique table does not contain true on construction";
}
/*
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
    runExpression();
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

TEST_F(managerTest, and2Test)
{
    ClassProject::BDD_ID AandB = testObj.and2(a,b);
    ASSERT_EQ(testObj.uniqueTable[AandB].low, testObj.False());
    ASSERT_EQ(testObj.uniqueTable[AandB].high, b);
}

TEST_F(managerTest, or2Test)
{
    ClassProject::BDD_ID AorB = testObj.or2(a,b);
    ASSERT_EQ(testObj.uniqueTable[AorB].low, b);
    ASSERT_EQ(testObj.uniqueTable[AorB].high, testObj.True());
}

TEST_F(managerTest, xor2Test)
{
    ClassProject::BDD_ID AxorB = testObj.xor2(a,b);
    ASSERT_EQ(testObj.uniqueTable[AxorB].low, b);
    ASSERT_EQ(testObj.uniqueTable[AxorB].high, testObj.neg(b));
}

TEST_F(managerTest, negTest)
{
    ClassProject::BDD_ID AandB = testObj.and2(a,b);
    ClassProject::BDD_ID negAandB = testObj.neg(AandB);
    ASSERT_EQ(testObj.uniqueTable[negAandB].low, testObj.True()) << "Incorrect result for neg";
    ASSERT_EQ(testObj.uniqueTable[negAandB].high, testObj.neg(b)) << "Incorrect result for neg";
}

TEST_F(managerTest, topVarTest)
{
    runExpression();
    ASSERT_EQ(testObj.topVar(6), 4);
    ASSERT_EQ(testObj.getTopVarName(6), "c");
    ASSERT_EQ(testObj.topVar(7), 2);
    ASSERT_EQ(testObj.getTopVarName(7), "a");
    ASSERT_EQ(testObj.topVar(8), 3);
    ASSERT_EQ(testObj.getTopVarName(8), "b");
    ASSERT_EQ(testObj.topVar(9), 2);
    ASSERT_EQ(testObj.getTopVarName(9), "a");
}
*/
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}