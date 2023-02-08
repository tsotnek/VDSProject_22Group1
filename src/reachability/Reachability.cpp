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
    
    if (initialState.size() != states.size())
        std::__throw_runtime_error("Missing initial state");

    if (transitions.size() != states.size())
        std::__throw_runtime_error("Missing transition functions");

    BDD_ID r = charcteristic_function;
    for (size_t i = 0; i < states.size(); i++)
         r = (stateVector.at(i)) ? coFactorTrue(r,states.at(i)) : coFactorFalse(r,states.at(i));
         
    return (r == True());
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) 
{
    if (transitionFunctions.size() != states.size())
        std::__throw_runtime_error("Incorrect size");
    transitions = transitionFunctions;

     //throw an exception if one of the provided BDD_IDs is unknown.
    for(size_t i = 0; i < transitions.size(); i++)
    {
        if(transitions.at(i) > uniqueTableSize()) //check that all transition bdd_ID values are all less than the total uniqueTablesize
            std::__throw_runtime_error("BDD_IDs is unknown for transition function");
    }

    if (initialState.size() == transitions.size()) symbolic_compute_reachable_states();
}

void Reachability::setInitState(const std::vector<bool> &stateVector) 
{
    if (stateVector.size() != states.size())
         std::__throw_runtime_error("Incorrect size");
    initialState = stateVector;


    if (initialState.size() == transitions.size()) symbolic_compute_reachable_states();
}

Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface::ReachabilityInterface(stateSize)
{
    if (stateSize == 0)
        std::__throw_runtime_error("Size cannot be zero");
    for (unsigned int i = 0; i < stateSize; i++ )
        states.push_back(createVar("s" + std::to_string(i)));
    for (unsigned int i = 0; i < stateSize; i++ )
        nstates.push_back(createVar("s'" + std::to_string(i)));
    
    //initial state bits are set to false
    std::vector<bool> zerosetter{stateSize, 0};
    initialState = zerosetter;

    //default transition function is the identity function
    transitions = states;
}

Reachability::~Reachability() { }

void Reachability::symbolic_compute_reachable_states()
{
    // Compute transition relation
    BDD_ID t = or2(and2(nstates.at(0),transitions.at(0)),nor2(nstates.at(0),transitions.at(0)));
    for (size_t i = 1; i < states.size(); i++)
        t = and2(t, or2(and2(nstates.at(i),transitions.at(i)),nor2(nstates.at(i),transitions.at(i))));

    // Compute caracteristic function of initial state 
    BDD_ID C_r = xnor2(states.at(0), (initialState.at(0)) ? True() : False());
    for (size_t i = 1; i < states.size(); i++) 
        C_r = and2(C_r, xnor2(states.at(i), (initialState.at(i)) ? True() : False()));

    BDD_ID C_rit = C_r; // Itterator for characteristic function

    do {
        C_r = C_rit;
        // Compute img(S')
        BDD_ID img_sp = and2(C_r, t);
        for (size_t i = states.size() - 1; i != SIZE_MAX; i--)
            img_sp = or2(coFactorTrue(img_sp, states.at(i)), coFactorFalse(img_sp, states.at(i)));

        // Compute img(S)
        BDD_ID img_s = and2(xnor2(states.at(0), nstates.at(0)),img_sp);
        for (size_t i = 1; i < states.size(); i++)
            img_s = and2(img_s, xnor2(states.at(i), nstates.at(i)));
        for (size_t i = states.size() - 1; i != SIZE_MAX; i--)
            img_s = or2(coFactorTrue(img_s, nstates.at(i)), coFactorFalse(img_s, nstates.at(i)));

        C_rit = or2(C_r, img_s);
    } while(C_r != C_rit);

    // Existential quantification of inputs
    std::set<BDD_ID> vars;
    findVars(C_r, vars);
    for (auto v : vars)
        if (std::find(states.begin(), states.end(), v) == states.end())
            C_r = or2(coFactorTrue(C_r,v),coFactorFalse(C_r,v));

    charcteristic_function = C_r;
}