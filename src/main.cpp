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
    cout << "Nothing implemented, yet" << endl;

    Manager testObj;

    testObj.createVar("a");
    testObj.createVar("b");
    testObj.createVar("c");
    testObj.createVar("d");


    BDD_ID f = testObj.and2(testObj.or2(2,3),testObj.and2(4,5));

#ifdef UNIQUE_PRINT_ENABLE
    PrintUniqueTable(testObj);
#endif
}




#ifdef UNIQUE_PRINT_ENABLE

void PrintUniqueTable(Manager &object)
{
    cout << "\n\n-------------------------------------------------------\n\n";
    cout << "---------------UNIQUE    TABLE-----------------\n\n";
    cout << "| BDD_ID|" << "  Low  |" << " High  |" << " Topvar |" << "Label" << endl;
    size_t BDD_count {0};
    for (auto item : object.uniqueTable)
    {   
        cout << "_______________________________________" << endl;
        cout << "|   " << BDD_count++ << "   |   " << item.low << "   |   " << item.high << "   |   " \
        << item.topVar << "    |  " << item.label << endl;
    }
}

#endif