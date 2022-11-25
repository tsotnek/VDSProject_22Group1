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
    return (f == True() || f == False()); 
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

    BDD_ID comp  = checkComputedTable(i,t,e);
    if (comp != -1) return computedTable[comp].result;

    BDD_ID tv = topVar(i);
    tv = (!isConstant(t) && topVar(t) < tv) ? topVar(t) : tv;
    tv = (!isConstant(e) && topVar(e) < tv) ? topVar(e) : tv;

    BDD_ID rHigh = ite(coFactorTrue(i, tv), coFactorTrue(t, tv), coFactorTrue(e, tv));
    BDD_ID rLow = ite(coFactorFalse(i, tv), coFactorFalse(t, tv), coFactorFalse(e, tv));

    if (rHigh == rLow) return rHigh;

    BDD_ID r = findOrAdd(tv, rLow, rHigh);

    // addToComputedTable(i,t,e,r);

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

BDD_ID Manager::neg(BDD_ID a) 
{
    return ite(a, False(), True());
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b) 
{ 
    return ite(a,b,False());
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b) 
{
    return ite(a,True(),b);
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b) 
{
    return ite(a, neg(b), b);
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b) 
{
    return neg(and2(a, b));
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b) 
{
    return neg(or2(a, b));
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b) 
{
    return neg(xor2(a, b));
}

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

/**
 * Checks if matching entry exists in unique table, if not creates one
 * Returns id of entry
 * @param a id of topvar
 * @param b id of low successor
 * @param c id of high successor
 */
BDD_ID Manager::findOrAdd(BDD_ID tv, BDD_ID low, BDD_ID high)
{
    for (int i = 0; i < uniqueTableSize(); i++)
        if (uniqueTable[i].topVar == tv && uniqueTable[i].high == high && uniqueTable[i].low == low) return i;

    uniqueTable.push_back(unique_table_entry {low, high, tv, std::to_string(uniqueTableSize())});
    return uniqueTableSize() - 1;
}

BDD_ID Manager::checkComputedTable(BDD_ID f, BDD_ID g, BDD_ID h)
{
    for (auto item : computedTable)
        if(item.f == f && item.g == g && item.h == h) return item.result;
    return -1;
}

void Manager::addToComputedTable(BDD_ID f, BDD_ID g, BDD_ID h, BDD_ID r)
{
    computedTable.push_back(computed_table_entry {f, g, h, r});
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

Manager::~Manager() { }