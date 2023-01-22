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

    transitionFunctions.push_back(fsm.neg(states.at(0)));
    transitionFunctions.push_back(fsm.neg(states.at(1)));

    fsm.setTransitionFunctions(transitionFunctions);

    vector<bool> initState = {true, false};
    fsm.setInitState(initState);

    cout << "ID, High, Low, Top Var, Label" << endl;
    for (BDD_ID i = 0; i < fsm.uniqueTableSize(); i++)
    {
        cout << i << ", " << fsm.highSuccesor(i) << ", " << fsm.lowSuccesor(i) << ", " 
            << fsm.topVar(i) << ", " << fsm.getLabel(i) << endl;
    }
    cout << "R: " << fsm.isReachable({false,false}) << endl;
    cout << "R: " << fsm.isReachable({false,true}) << endl;
    cout << "R: " << fsm.isReachable({true,false}) << endl;
    cout << "R: " << fsm.isReachable({true,true}) << endl;
}