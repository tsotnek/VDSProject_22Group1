#include <vector>
#include <string>

#include "Manager.h"

/**
 * CreateVar method takes one parameter 
 */
ClassProject::BDD_ID ClassProject::Manager::createVar(const std::string &label) 
{
    uniqueTable.push_back(ClassProject::unique_table_entry());
    uniqueTable.back().id = uniqueTable.size();
    uniqueTable.back().low = 1;
    uniqueTable.back().high = 2;
    uniqueTable.back().topVar = uniqueTable.size();
    uniqueTable.back().label = label;
    return uniqueTable.back().id;
}

const ClassProject::BDD_ID &ClassProject::Manager::True() 
{
    return uniqueTable[1].id; 
}

const ClassProject::BDD_ID &ClassProject::Manager::False() 
{ 
    return uniqueTable[0].id; 
}

bool ClassProject::Manager::isConstant(ClassProject::BDD_ID f) 
{
    return (f == 1 || f == 2); 
}

bool ClassProject::Manager::isVariable(ClassProject::BDD_ID x) 
{
    return (uniqueTable[x-1].id == uniqueTable[x-1].topVar);
}

ClassProject::BDD_ID ClassProject::Manager::topVar(ClassProject::BDD_ID f) 
{
    return uniqueTable[f-1].topVar; 
}

ClassProject::BDD_ID ClassProject::Manager::ite(ClassProject::BDD_ID i, ClassProject::BDD_ID t, ClassProject::BDD_ID e) 
{
    if (i == 1) return e;
    if (i == 2) return t;

    ClassProject::BDD_ID topVar = uniqueTable[i-1].topVar;
    topVar = (t > 2 && uniqueTable[t-1].topVar < topVar) ? uniqueTable[t-1].topVar : topVar;
    topVar = (e > 2 && uniqueTable[e-1].topVar < topVar) ? uniqueTable[e-1].topVar : topVar;

    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorTrue(ClassProject::BDD_ID f, ClassProject::BDD_ID x) 
{
    if (f == x) return uniqueTable[f-1].high;

    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorFalse(ClassProject::BDD_ID f, ClassProject::BDD_ID x) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::coFactorTrue(ClassProject::BDD_ID f)  { return 0; }

ClassProject::BDD_ID ClassProject::Manager::coFactorFalse(ClassProject::BDD_ID f) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::neg(ClassProject::BDD_ID a) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::and2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::or2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) 
{
    return ite(a,2,b);
}

ClassProject::BDD_ID ClassProject::Manager::xor2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::nand2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::nor2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

ClassProject::BDD_ID ClassProject::Manager::xnor2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) { return 0; }

std::string ClassProject::Manager::getTopVarName(const ClassProject::BDD_ID &root) 
{
    return uniqueTable[uniqueTable[root-1].topVar].label;
}

void ClassProject::Manager::findNodes(const ClassProject::BDD_ID &root, std::set<ClassProject::BDD_ID> &nodes_of_root) { }

void ClassProject::Manager::findVars(const ClassProject::BDD_ID &root, std::set<ClassProject::BDD_ID> &vars_of_root) { }

size_t ClassProject::Manager::uniqueTableSize() 
{
    return uniqueTable.size();
}

ClassProject::Manager::Manager(void)
{
    uniqueTable.push_back(ClassProject::unique_table_entry());
    uniqueTable.push_back(ClassProject::unique_table_entry());
    uniqueTable[0].id = 1;
    uniqueTable[1].id = 2;
    uniqueTable[0].high = 0;
    uniqueTable[1].high = 1;
    uniqueTable[0].low = 0;
    uniqueTable[1].low = 1;
    uniqueTable[0].topVar = 0;
    uniqueTable[1].topVar = 1;
    uniqueTable[0].label = "False";
    uniqueTable[1].label = "True";
}

ClassProject::Manager::~Manager() {}