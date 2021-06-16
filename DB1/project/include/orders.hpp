#pragma once

#include <vector>

#include <sqlite3.h>

#include "bprinter/table_printer.h"

#include "base.hpp"

class Orders : public Base {
    struct Record : public Base::Record {
        int id;
        int deviceID;
        int clientID;
        std::string state;

        Record(sqlite3_stmt* stmt);
        void print(bprinter::TablePrinter& out) const;
    };

public:
    Orders(sqlite3* db);
};
