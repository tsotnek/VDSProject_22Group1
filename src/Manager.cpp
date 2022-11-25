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
    return (f == True() && f == False()); 
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

    // TODO: check computed table

    BDD_ID tv = topVar(i);
    tv = (!isConstant(t) && topVar(t) < tv) ? topVar(t) : tv;
    tv = (!isConstant(e) && topVar(t) < tv) ? topVar(e) : tv;

    BDD_ID rHigh = ite(coFactorTrue(i, tv), coFactorTrue(t, tv), coFactorTrue(e, tv));
    BDD_ID rLow = ite(coFactorFalse(i, tv), coFactorFalse(t, tv), coFactorFalse(e, tv));

    if (rHigh == rLow) return rHigh;

    BDD_ID r = findOrAdd(tv, rLow, rHigh);

    // TODO: add to computed table

    return r;
}

/**
 * Returns positive cofactor of an expression with respect to a specified variable
 * @param f id of expression
 * @param x id of variable
 */
BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x) 
{
    if (isConstant(f)) return f;
    if (topVar(f) == x) return getHigh(f);

    BDD_ID T = coFactorTrue(getHigh(f), x);
    BDD_ID F = coFactorTrue(getLow(f), x);

    return ite(topVar(f),T,F);
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x) 
{
    if (isConstant(f)) return f;
    if (topVar(f) == x) return getLow(f);

    BDD_ID T = coFactorFalse(getHigh(f), x);
    BDD_ID F = coFactorFalse(getLow(f), x);

    return ite(topVar(f), T, F);
}

BDD_ID Manager::coFactorTrue(BDD_ID f)  
{
    return coFactorTrue(f, topVar(f));
}

BDD_ID Manager::coFactorFalse(BDD_ID f) 
{
    return coFactorFalse(f, topVar(f));
}

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
 * Returns high result of id
 * @param a id to be evaluated
 */
BDD_ID Manager::getHigh(BDD_ID a)
{
    return uniqueTable[a].high;
}

/**
 * Returns low result of id
 * @param a id to be evaluated
 */
BDD_ID Manager::getLow(BDD_ID a)
{
    return uniqueTable[a].low;
}

BDD_ID Manager::findOrAdd(BDD_ID a, BDD_ID b, BDD_ID c)
{
    for (int i = 0; i < uniqueTableSize(); i++)
        if (uniqueTable[i].topVar == a && uniqueTable[i].high == b && uniqueTable[i].low == c) return i;

    uniqueTable.push_back(unique_table_entry {b, c, a, std::to_string(uniqueTableSize())});
    return uniqueTableSize() - 1;
}

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