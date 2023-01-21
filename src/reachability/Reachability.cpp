#include "Reachability.h"

#include <algorithm>

using namespace ClassProject;

const std::vector<BDD_ID> &Reachability::getStates() const
{
    return states;
}

bool Reachability::isReachable(const std::vector<bool> &stateVector) 
{
    if (stateVector.size() != states.size())
        std::__throw_runtime_error("Incorrect size");
    
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) 
{
    if (transitionFunctions.size() != states.size())
        std::__throw_runtime_error("Incorrect size");
    transitions = transitionFunctions;
}

void Reachability::setInitState(const std::vector<bool> &stateVector) 
{
    if (stateVector.size() != states.size())
        std::__throw_runtime_error("Incorrect size");
    initialState = stateVector;
}

explicit Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface::ReachabilityInterface(stateSize)
{
    if (stateSize == 0)
        std::__throw_runtime_error("Size cannot be zero");
    for (unsigned int i = 0; i < stateSize; i++ )
        states.push_back(createVar("s" + std::to_string(i)));
}