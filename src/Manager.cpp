#include "Manager.h"

#include <stdexcept>

using namespace ClassProject;

/**
 * Creates a new variable in the unique table
 * @param label Label for the variable
 */
BDD_ID Manager::createVar(const std::string &label) 
{
    return createNode(False(),True(),uniqueTableSize(),label);
}

/**
 * Returns the id of the "True" case
 */
const BDD_ID &Manager::True() 
{
    return TrueID;
}

/**
 * Returns the id of the "False" case
 */
const BDD_ID &Manager::False() 
{ 
    return FalseID; 
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
 * Evaluates if expression represents a variable
 * @param x id to evaluate
 */
bool Manager::isVariable(BDD_ID x) 
{
    return (topVar(x) == x && x != True() && x != False());
}

/**
 * Returns top variable of expression
 * @param id id to evaluate
 */
BDD_ID Manager::topVar(ClassProject::BDD_ID f) 
{
    return uniqueTable[f].topVar; 
}

/**
 * Returns the result of an if-then-else operation
 * @param i id of if expression
 * @param t id of then case
 * @param e id of else case
 */
BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e) 
{
    if (isConstant(i)) return (i == True()) ? t : e;
    if (auto comp = checkComputedTable(i,t,e); comp != -1) return comp;

    BDD_ID tv = topVar(i);
    tv = (!isConstant(t) && topVar(t) < tv) ? topVar(t) : tv;
    tv = (!isConstant(e) && topVar(e) < tv) ? topVar(e) : tv;

    BDD_ID rHigh = ite(coFactorTrue(i, tv), coFactorTrue(t, tv), coFactorTrue(e, tv));
    BDD_ID rLow = ite(coFactorFalse(i, tv), coFactorFalse(t, tv), coFactorFalse(e, tv));

    if (rHigh == rLow) return rHigh;

    BDD_ID r = findOrAdd(tv, rLow, rHigh);
    addToComputedTable(i,t,e,r);

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
    if (topVar(f) == x) return highSuccesor(f);

    BDD_ID T = coFactorTrue(highSuccesor(f), x);
    BDD_ID F = coFactorTrue(lowSuccesor(f), x);

    return ite(topVar(f),T,F);
}

/**
 * Returns negative cofactor of an expression with respect to a specified variable
 * @param f id of expression
 * @param x id of variable
 */
BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x) 
{
    if (isConstant(f)) return f;
    if (topVar(f) == x) return lowSuccesor(f);

    BDD_ID T = coFactorFalse(highSuccesor(f), x);
    BDD_ID F = coFactorFalse(lowSuccesor(f), x);

    return ite(topVar(f), T, F);
}

/**
 * Returns positive cofactor of an expression with respect to its top variable
 * @param f id of expression to be evaluated
 */
BDD_ID Manager::coFactorTrue(BDD_ID f)  
{
    return coFactorTrue(f, topVar(f));
}

/**
 * Returns negative cofactor of an expression with respect to its top variable
 * @param f id of expression to be evaluated
 */
BDD_ID Manager::coFactorFalse(BDD_ID f) 
{
    return coFactorFalse(f, topVar(f));
}

/**
 * Returns negation of expression
 * @param a id of expression to be evaluated
 */
BDD_ID Manager::neg(BDD_ID a) 
{
    return ite(a, False(), True());
}

/**
 * Returns result of and operation between two expressions
 * @param a id of first expression
 * @param b id of seccond expression
 */
BDD_ID Manager::and2(BDD_ID a, BDD_ID b) 
{ 
    return ite(a,b,False());
}

/**
 * Returns result of or operation between two expressions
 * @param a id of first expression
 * @param b id of seccond expression
 */
BDD_ID Manager::or2(BDD_ID a, BDD_ID b) 
{
    return ite(a,True(),b);
}

/**
 * Returns result of xor operation between two expressions
 * @param a id of first expression
 * @param b id of seccond expression
 */
BDD_ID Manager::xor2(BDD_ID a, BDD_ID b) 
{
    return ite(a, neg(b), b);
}

/**
 * Returns result of nand operation between two expressions
 * @param a id of first expression
 * @param b id of seccond expression
 */
BDD_ID Manager::nand2(BDD_ID a, BDD_ID b) 
{
    return neg(and2(a, b));
}

/**
 * Returns result of nor operation between two expressions
 * @param a id of first expression
 * @param b id of seccond expression
 */
BDD_ID Manager::nor2(BDD_ID a, BDD_ID b) 
{
    return neg(or2(a, b));
}

/**
 * Returns result of xnor operation between two expressions
 * @param a id of first expression
 * @param b id of seccond expression
 */
BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b) 
{
    return neg(xor2(a, b));
}

/**
 * Returns low successor of node
 * @param a id to be evaluated
 */
BDD_ID Manager::highSuccesor(BDD_ID a)
{
    return uniqueTable[a].high;
}

/**
 * Returns low successor of node
 * @param a id to be evaluated
 */
BDD_ID Manager::lowSuccesor(BDD_ID a)
{
    return uniqueTable[a].low;
}

/**
 * Checks if matching entry exists in unique table, if not creates one
 * Returns id of entry
 * @param tv id of topvar
 * @param low id of low successor
 * @param high id of high successor
 */
BDD_ID Manager::findOrAdd(BDD_ID tv, BDD_ID low, BDD_ID high)
{
    std::string key = getLabel(tv) + getLabel(low) + getLabel(high);
    try
    {
        return uniqueTableMap.at(key);
    }
    catch (const std::out_of_range& e)
    {
        return createNode(low, high, tv, std::to_string(uniqueTableSize()));
    }
}

/**
 * Evaluates if expression has already been computed
 * Returns id if expression exists, else -1
 * @param f id of if expression
 * @param g id of then expression
 * @param h id of else expression
 */
BDD_ID Manager::checkComputedTable(BDD_ID f, BDD_ID g, BDD_ID h)
{
    std::string key = getLabel(f) + getLabel(g) + getLabel(h);
    try
    {
        return computedTable.at(key);
    }
    catch (const std::out_of_range& e)
    {
        return -1;
    }
}

/**
 * Adds an expression to the computed table
 * @param f id of if expression
 * @param g id of then expression
 * @param h id of else expression
 * @param r id of result
 */
void Manager::addToComputedTable(BDD_ID f, BDD_ID g, BDD_ID h, BDD_ID r)
{
    std::string key = getLabel(f) + getLabel(g) + getLabel(h);
    computedTable[key] = r;
}

/**
 * Returns label of top variable of expression
 * @param root id to be evaluated
 */
std::string Manager::getTopVarName(const BDD_ID &root) 
{
    return getLabel(topVar(root));
}

/**
 * Finds the set of nodes which are reachable from a given node
 * @param root id to be evaluated
 * @param nodes_of_root empty set which will recive result of function
 */ 
void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root)
{
    nodes_of_root.insert(root);
    if (!nodes_of_root.count(lowSuccesor(root))) findNodes(lowSuccesor(root), nodes_of_root);
    if (!nodes_of_root.count(highSuccesor(root))) findNodes(highSuccesor(root), nodes_of_root);
}

/**
 * Finds the set of variables which are reachable from a given node
 * @param root id to be evaluated
 * @param vars_of_root empty set which will recive result of function
 */
void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root)
{
    std::set<BDD_ID> nodes;
    findNodes(root, nodes);
    for (auto node : nodes) if (!isConstant(node)) vars_of_root.insert(topVar(node));
}


/**
 * Returns number of current entries in the unique table
 */
size_t Manager::uniqueTableSize() 
{
    return uniqueTable.size();
}

/**
 * Creates a node in the unique table and returns its id
 * @param l id of low successor
 * @param h id of high successor
 * @param tv id of top variable
 * @param label label of node
 */
BDD_ID Manager::createNode(BDD_ID l, BDD_ID h, BDD_ID tv, std::string label)
{
    uniqueTable.push_back(unique_table_entry {l,h,tv,label});
    std::string key = getLabel(tv) + getLabel(l) + getLabel(h);
    uniqueTableMap[key] = uniqueTableSize() - 1;
    return uniqueTableSize() - 1;
}

/**
 * Returns label of a unique table entry
 * @param f id to be evaluated
 */
std::string Manager::getLabel(BDD_ID f)
{
    return uniqueTable[f].label;
}

/**
 * Constructor creates entries for the "True" and "False" cases in the unique table
 */
Manager::Manager(void)
{
    FalseID = createNode(0,0,0,"False");
    TrueID = createNode(1,1,1,"True");
}

Manager::~Manager() { }