#include "Manager.h"

#include <iostream>

using ClassProject::Manager;
using ClassProject::BDD_ID;

int main(int argc, char* argv[])
{
    Manager m;

    BDD_ID a = m.createVar("a");
    BDD_ID b = m.createVar("b");
    BDD_ID c = m.createVar("c");
    BDD_ID d = m.createVar("d");

    BDD_ID f = m.and2(m.and2(c,d),m.or2(a,b));

    std::set<BDD_ID> nodes;
    std::set<BDD_ID> vars;

    m.findNodes(f, nodes);
    m.findVars(f, vars);
}