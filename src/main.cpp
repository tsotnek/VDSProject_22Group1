#include "Manager.h"
#include "reachability/Reachability.h"

#include <iostream>

using std::cout;
using std::endl;
using std::vector;

using ClassProject::Reachability;
using ClassProject::Manager;
using ClassProject::BDD_ID;

int main(int argc, char* argv[])
{
    
    Reachability fsm(2);
    vector<BDD_ID> transitionFunctions;
    vector<BDD_ID> states = fsm.getStates();

    // Example from lecture 4
    BDD_ID x1 = fsm.createVar("x1");
    BDD_ID x2 = fsm.createVar("x2");
    transitionFunctions.push_back(fsm.and2(fsm.neg(x1), fsm.or2(states.at(0),states.at(1))));
    transitionFunctions.push_back(fsm.and2(x2,fsm.or2(x1,fsm.or2(states.at(0),states.at(1)))));

    fsm.setTransitionFunctions(transitionFunctions);

    vector<bool> initState = {false, false};
    fsm.setInitState(initState);

    cout << "ID, High, Low, Top Var, Label" << endl;
    for (BDD_ID i = 0; i < fsm.uniqueTableSize(); i++)
    {
        cout << i << ", " << fsm.highSuccesor(i) << ", " << fsm.lowSuccesor(i) << ", " 
            << fsm.topVar(i) << ", " << fsm.getLabel(i) << endl;
    }

    cout << endl << "C_r: " << fsm.getCr() << endl;
    
    cout << endl << "(s0..sn): (reachable)" << endl;
    cout << "00: " << fsm.isReachable({false,false}) << endl;
    cout << "01: " << fsm.isReachable({false,true}) << endl;
    cout << "10: " << fsm.isReachable({true,false}) << endl;
    cout << "11: " << fsm.isReachable({true,true}) << endl;
}