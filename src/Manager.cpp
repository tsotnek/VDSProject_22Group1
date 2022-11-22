#include <vector>
#include <string>

#include "Manager.h"

/**
 * Creates a new variable at the end of the unique table
 * @param label Label for the variable
 */
ClassProject::BDD_ID ClassProject::Manager::createVar(const std::string &label) 
{
    uniqueTable.push_back(ClassProject::unique_table_entry {0,1,uniqueTableSize(),label});
    return uniqueTable.back().topVar;
}

/**
 * Returns the id of the "True" case
 */
const ClassProject::BDD_ID &ClassProject::Manager::True() 
{
    return uniqueTable[1].topVar; 
}

/**
 * Returns the id of the "False" case
 */
const ClassProject::BDD_ID &ClassProject::Manager::False() 
{ 
    return uniqueTable[0].topVar; 
}

/**
 * Evaluates if id represents a constant
 * @param f id to evaluate
 */
bool ClassProject::Manager::isConstant(ClassProject::BDD_ID f) 
{
    return (f > 1); 
}

/**
 * Evaluates if id represents a variable
 * @param x id to evaluate
 */
bool ClassProject::Manager::isVariable(ClassProject::BDD_ID x) 
{
    return (topVar(x) == x);
}

/**
 * Returns top variable of id
 * @param id id to evaluate
 */
ClassProject::BDD_ID ClassProject::Manager::topVar(ClassProject::BDD_ID f) 
{
    return uniqueTable[f].topVar; 
}

ClassProject::BDD_ID ClassProject::Manager::ite(ClassProject::BDD_ID i, ClassProject::BDD_ID t, ClassProject::BDD_ID e) 
{
    if (i == False()) return e;
    if (i == True()) return t;

    ClassProject::BDD_ID tv = topVar(i);
    tv = (!isConstant(t) && topVar(t) < tv) ? topVar(t) : tv;
    tv = (!isConstant(e) && topVar(t) < tv) ? topVar(e) : tv;

    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorTrue(ClassProject::BDD_ID f, ClassProject::BDD_ID x) 
{
    if (f == x) return uniqueTable[f].high;

    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorFalse(ClassProject::BDD_ID f, ClassProject::BDD_ID x) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::coFactorTrue(ClassProject::BDD_ID f)  { return 0; }

ClassProject::BDD_ID ClassProject::Manager::coFactorFalse(ClassProject::BDD_ID f) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::neg(ClassProject::BDD_ID a) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::and2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::or2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) 
{
    return ite(a,True(),b);
}

ClassProject::BDD_ID ClassProject::Manager::xor2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::nand2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::nor2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::xnor2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

/**
 * Returns label of top variable of id
 * @param root id to be evaluated
 */
std::string ClassProject::Manager::getTopVarName(const ClassProject::BDD_ID &root) 
{
    return uniqueTable[uniqueTable[root].topVar].label;
}

void ClassProject::Manager::findNodes(const ClassProject::BDD_ID &root, std::set<ClassProject::BDD_ID> &nodes_of_root) { }

void ClassProject::Manager::findVars(const ClassProject::BDD_ID &root, std::set<ClassProject::BDD_ID> &vars_of_root) { }


/**
 * Returns number of current entries in the unique table
 */
size_t ClassProject::Manager::uniqueTableSize() 
{
    return uniqueTable.size();
}

/**
 * Constructor creates entries for the "True" and "False" cases in the unique table
 */
ClassProject::Manager::Manager(void)
{
    uniqueTable.push_back(ClassProject::unique_table_entry {0,0,0,"False"});
    uniqueTable.push_back(ClassProject::unique_table_entry {1,1,1,"True"});
}

ClassProject::Manager::~Manager() {}