#include <iostream>
#include <memory>
#include <vector>

#include "db.hpp"
#include "util.hpp"
#include "base.hpp"
#include "clients.hpp"
#include "orders.hpp"

int main()
{
    DB db;

    std::vector<std::unique_ptr<Base>> tables;
    {
        sqlite3* d = db.raw();
        tables.emplace_back(std::make_unique<Clients>(d));
        tables.emplace_back(std::make_unique<Orders>(d));
    }

    unsigned short i = 0;

    tables[i]->print();

    bool flag = true;
    while (flag) {
        switch (getch()) {
            case 27: // esc
                switch (getch()) {
                    case '[':
                        switch (getch()) {
                            case 65: // arrow up
                                tables[i]->prev();
                                break;
                            case 66: // arrow down
                                tables[i]->next();
                                break;
                            case 67: // arrow right
                                if (i < tables.size() - 1) {
                                    ++i;
                                }
                                tables[i]->print();
                                break;
                            case 68: // arrow left
                                if (i > 0) {
                                    --i;
                                }
                                tables[i]->print();
                                break;
                        }
                        break;
                }
                break;
            case '\n':
                tables[i]->box();
                tables[i]->print();
                break;
            case 'q':
                flag = false;
                break;
        }
    }

    return 0;
}

// vim: fdl=1
