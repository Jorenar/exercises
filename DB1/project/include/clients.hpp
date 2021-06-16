#pragma once

#include <vector>

#include <sqlite3.h>

#include "bprinter/table_printer.h"

#include "base.hpp"

class Clients : public Base {
    struct Record : public Base::Record {
        int id;
        std::string name;
        std::string surname;
        std::string tel;
        std::string email;
        int orders;

        Record(sqlite3_stmt* stmt);
        void print(bprinter::TablePrinter& out) const;
        void detailed() const;
        void edit();
    };

public:
    Clients(sqlite3* db);
};
