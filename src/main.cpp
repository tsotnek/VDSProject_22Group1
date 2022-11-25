//TEST
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"

using ClassProject::Manager;
using ClassProject::BDD_ID;
using std::cout;
using std::endl;

//(~DISABLE)ENABLE PRINTING OF UNIQUE TABLE
#define UNIQUE_PRINT_ENABLE



#ifdef UNIQUE_PRINT_ENABLE
void PrintUniqueTable(Manager &object);
#endif

int main(int argc, char* argv[])
{
    ClassProject::Manager m;

    ClassProject::BDD_ID a = m.createVar("a");
    ClassProject::BDD_ID b = m.createVar("b");
    ClassProject::BDD_ID c = m.createVar("c");
    ClassProject::BDD_ID d = m.createVar("d");

    ClassProject::BDD_ID f = m.and2(m.and2(c,d),m.or2(a,b));

    PrintUniqueTable(m);
}




#ifdef UNIQUE_PRINT_ENABLE

void PrintUniqueTable(Manager &object)
{
    //cout << "\n\n-------------------------------------------------------\n\n";
    //cout << "---------------UNIQUE    TABLE-----------------\n\n";
    cout << "| BDD_ID|" << "  Low  |" << " High  |" << " Topvar |" << "Label" << endl;
    cout << "_______________________________________" << endl;
    size_t BDD_count {0};
    for (auto item : object.uniqueTable)
    {   
        //cout << "_______________________________________" << endl;
        cout << "|   " << BDD_count++ << "   |   " << item.low << "   |   " << item.high << "   |   " \
        << item.topVar << "    |  " << item.label << endl;
    }
}

#endif