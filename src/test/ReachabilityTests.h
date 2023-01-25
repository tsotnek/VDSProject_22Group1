#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include "../reachability/Reachability.h"

using namespace ClassProject;

struct ReachabilityTest : testing::Test {

    std::unique_ptr<ClassProject::ReachabilityInterface> fsm2 = std::make_unique<ClassProject::Reachability>(2);

    std::vector<BDD_ID> stateVars2 = fsm2->getStates();
    std::vector<BDD_ID> transitionFunctions;

};

struct rTest : testing::Test {};

TEST_F(ReachabilityTest, HowTo_Example) { /* NOLINT */

    BDD_ID s0 = stateVars2.at(0);
    BDD_ID s1 = stateVars2.at(1);

    transitionFunctions.push_back(fsm2->neg(s0)); // s0' = not(s0)
    transitionFunctions.push_back(fsm2->neg(s1)); // s1' = not(s1)
    fsm2->setTransitionFunctions(transitionFunctions);

    fsm2->setInitState({false,false});

    ASSERT_TRUE(fsm2->isReachable({false, false}));
    ASSERT_FALSE(fsm2->isReachable({false, true}));
    ASSERT_FALSE(fsm2->isReachable({true, false}));
    ASSERT_TRUE(fsm2->isReachable({true, true}));
}

TEST_F(rTest, lecture_4_example) {
    Reachability fsm(2);
    std::vector<BDD_ID> transitionFunctions;
    std::vector<BDD_ID> states = fsm.getStates();

    BDD_ID x1 = fsm.createVar("x1");
    BDD_ID x2 = fsm.createVar("x2");
    BDD_ID s0 = states.at(0);
    BDD_ID s1 = states.at(1);
    transitionFunctions.push_back(fsm.and2( fsm.neg(x1), 
                                            fsm.or2(s0,s1)));
    transitionFunctions.push_back(fsm.and2( x2,
                                            fsm.or2(x1,
                                                    fsm.or2(s0,s1))));
    fsm.setTransitionFunctions(transitionFunctions);

    fsm.setInitState({false, false});
    
    ASSERT_TRUE(fsm.isReachable({false,false}));
    ASSERT_TRUE(fsm.isReachable({false,true}));
    ASSERT_FALSE(fsm.isReachable({true,false}));
    ASSERT_FALSE(fsm.isReachable({true,true}));
}

TEST_F(rTest, lab_5_serial_read) { // only control logic (without reset)
    Reachability fsm(5);
    std::vector<BDD_ID> transitionFunctions;
    std::vector<BDD_ID> states = fsm.getStates();

    BDD_ID rxd = fsm.createVar("rxd");
    BDD_ID s0 = states.at(0); // Cnt_En
    BDD_ID s1 = states.at(1); // Cnt_s_0 (LSB)
    BDD_ID s2 = states.at(2); // Cnt_s_1
    BDD_ID s3 = states.at(3); // Cnt_s_2 (MSB)
    BDD_ID s4 = states.at(4); // Valid

    transitionFunctions.push_back(fsm.or2(  fsm.nor2(s0,rxd), 
                                            fsm.and2(s0, 
                                                     fsm.nand2( s3, 
                                                                fsm.and2(s2, s1)))));
    transitionFunctions.push_back(fsm.and2( s0,
                                            fsm.neg(s1)));
    transitionFunctions.push_back(fsm.and2( s0, 
                                            fsm.xor2(s1,s2)));
    transitionFunctions.push_back(fsm.and2( s0, 
                                            fsm.or2(fsm.and2(   fsm.neg(s3),
                                                                fsm.and2(s2,s1)),
                                                    fsm.and2(   s3,
                                                                fsm.nand2(s2,s1)))));
    transitionFunctions.push_back(fsm.and2( s3,
                                            fsm.and2(s2,s1)));

    fsm.setTransitionFunctions(transitionFunctions);
    fsm.setInitState({false, false, false, false, false});

    std::set<uint8_t> expectTrue({0, 1, 3, 5, 7, 9, 11, 13, 15, 16});
    std::vector<bool> s(5, false);
    for (u_int8_t i = 0; i <= 0b11111; i++)
    {
        bool r = (expectTrue.find(i) != expectTrue.end());
        s.at(0) = i & 0b00001;
        s.at(1) = i & 0b00010;
        s.at(2) = i & 0b00100;
        s.at(3) = i & 0b01000;
        s.at(4) = i & 0b10000;
        ASSERT_EQ(fsm.isReachable(s), r) << "For state 0d" << std::to_string(i);
    }
}

TEST_F(rTest, throw_error_test) {
    Reachability fsm(2);
    EXPECT_THROW(fsm.setInitState({false}), std::runtime_error) << "Missing error for init size too small";
    EXPECT_THROW(fsm.setInitState({false,false,false}), std::runtime_error) << "Missing error for init size too large";
    EXPECT_THROW(fsm.setTransitionFunctions({fsm.False()}), std::runtime_error) << "Missing error for transition function size too small";
    EXPECT_THROW(fsm.setTransitionFunctions({fsm.False(), fsm.False(), fsm.False()}), std::runtime_error) << "Missing error for transition function size too big";
    EXPECT_THROW(fsm.isReachable({false}), std::runtime_error) << "Missing error for state size too small";
    EXPECT_THROW(fsm.isReachable({false,false,false}), std::runtime_error) << "Missing error for state size too big";
}
#endif
