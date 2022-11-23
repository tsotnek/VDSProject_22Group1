#include <vector>
#include <string>
#include <iostream>
#include "Manager.h"

using namespace ClassProject;
/**
 * Creates a new variable at the end of the unique table
 * @param label Label for the variable
 */
BDD_ID Manager::createVar(const std::string &label) 
{
    uniqueTable.push_back(unique_table_entry {0,1,uniqueTableSize(),label});
    return uniqueTable.back().topVar;
}

/**
 * Returns the id of the "True" case
 */
const BDD_ID &Manager::True() 
{
    return uniqueTable[1].topVar; 
}

/**
 * Returns the id of the "False" case
 */
const BDD_ID &Manager::False() 
{ 
    return uniqueTable[0].topVar; 
}

/**
 * Evaluates if id represents a constant
 * @param f id to evaluate
 */
bool Manager::isConstant(BDD_ID f) 
{
    return (f < 1); 
}

/**
 * Evaluates if id represents a variable
 * @param x id to evaluate
 */
bool Manager::isVariable(BDD_ID x) 
{
    return (topVar(x) == x);
}

/**
 * Returns top variable of id
 * @param id id to evaluate
 */
BDD_ID Manager::topVar(ClassProject::BDD_ID f) 
{
    return uniqueTable[f].topVar; 
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e) 
{
    if (i == False()) return e;
    if (i == True()) return t;

    BDD_ID tv = topVar(i);
    tv = (!isConstant(t) && topVar(t) < tv) ? topVar(t) : tv;
    tv = (!isConstant(e) && topVar(t) < tv) ? topVar(e) : tv;

    return 0;
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x) 
{
    if (f == x) return uniqueTable[f].high;

    return 0;
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x) { return 0; }

BDD_ID Manager::coFactorTrue(BDD_ID f)  { return 0; }

BDD_ID Manager::coFactorFalse(BDD_ID f) { return 0; }

BDD_ID Manager::neg(BDD_ID a) { return 0; }

BDD_ID Manager::and2(BDD_ID a, BDD_ID b) { return 0; }

BDD_ID Manager::or2(BDD_ID a, BDD_ID b) 
{
    return ite(a,True(),b);
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b) { return 0; }

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b) { return 0; }

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b) { return 0; }

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b) { return 0; }

/**
 * Returns label of top variable of id
 * @param root id to be evaluated
 */
std::string Manager::getTopVarName(const BDD_ID &root) 
{
    return uniqueTable[uniqueTable[root].topVar].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) { }

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) { }


/**
 * Returns number of current entries in the unique table
 */
size_t Manager::uniqueTableSize() 
{
    return uniqueTable.size();
}

/**
 * Constructor creates entries for the "True" and "False" cases in the unique table
 */
Manager::Manager(void)
{
    uniqueTable.push_back(unique_table_entry {0,0,0,"False"});
    uniqueTable.push_back(unique_table_entry {1,1,1,"True"});
}

Manager::~Manager() 
{
    std::cout << "Manager class destroyed!" << std::endl; 
}