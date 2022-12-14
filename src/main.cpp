#include "Manager.h"

using ClassProject::Manager;
using ClassProject::BDD_ID;

int main(int argc, char* argv[])
{
    ClassProject::Manager m;

    ClassProject::BDD_ID a = m.createVar("a");
    ClassProject::BDD_ID b = m.createVar("b");
    ClassProject::BDD_ID c = m.createVar("c");
    ClassProject::BDD_ID d = m.createVar("d");

    ClassProject::BDD_ID f = m.and2(m.and2(c,d),m.or2(a,b));
}