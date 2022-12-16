#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

#include "ManagerInterface.h"


namespace ClassProject {

    struct unique_table_entry {
        BDD_ID low;
        BDD_ID high;
        BDD_ID topVar;
        std::string label;
    };

    class Manager: public ManagerInterface {
        public:
            BDD_ID createVar(const std::string &label) override;

            const BDD_ID &True() override;

            const BDD_ID &False() override;

            bool isConstant(BDD_ID f) override;

            bool isVariable(BDD_ID x) override;

            BDD_ID topVar(BDD_ID f) override;

            BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override;

            BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override;

            BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override;

            BDD_ID coFactorTrue(BDD_ID f) override;

            BDD_ID coFactorFalse(BDD_ID f) override;

            BDD_ID neg(BDD_ID a) override;

            BDD_ID and2(BDD_ID a, BDD_ID b) override;

            BDD_ID or2(BDD_ID a, BDD_ID b) override;

            BDD_ID xor2(BDD_ID a, BDD_ID b) override;

            BDD_ID nand2(BDD_ID a, BDD_ID b) override;

            BDD_ID nor2(BDD_ID a, BDD_ID b) override;

            BDD_ID xnor2(BDD_ID a, BDD_ID b) override;

            std::string getTopVarName(const BDD_ID &root) override;

            void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

            void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

            size_t uniqueTableSize() override;

            BDD_ID highSuccesor(BDD_ID a);

            BDD_ID lowSuccesor(BDD_ID a);

            std::string getLabel(BDD_ID f);

            Manager(void);

            ~Manager();
        
        private:
            BDD_ID TrueID;

            BDD_ID FalseID;

            std::vector<unique_table_entry> uniqueTable;

            std::unordered_map<size_t, BDD_ID> computedTable;

            std::unordered_map<size_t, BDD_ID> uniqueTableMap;

            BDD_ID findOrAdd(BDD_ID a, BDD_ID b, BDD_ID c);

            BDD_ID checkComputedTable(BDD_ID f, BDD_ID g, BDD_ID h);

            BDD_ID createNode(BDD_ID l, BDD_ID h, BDD_ID tv, std::string label);

            void addToComputedTable(BDD_ID f, BDD_ID g, BDD_ID h, BDD_ID r);
    };
}

#endif
