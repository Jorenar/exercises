#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <sqlite3.h>

#include "bprinter/table_printer.h"

class Base {
    static std::vector<std::string> tabs;
    std::size_t startline;
    sqlite3* db;
    sqlite3_stmt* stmt;
protected:
    bprinter::TablePrinter tp;

    Base(sqlite3* db, std::string t, std::string query);
    template<typename R> void readRecords();

    struct Record {
        virtual void print(bprinter::TablePrinter&) const {}
        virtual void detailed() const {}
        virtual void edit() {}
    };

    std::string tab;
    std::size_t current;
    std::size_t size() const;
    std::vector<std::unique_ptr<Record> > records;

public:
    void print();
    void next();
    void prev();
    void box();
};

template<typename R>
void Base::readRecords()
{
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        records.emplace_back(std::make_unique<R>(stmt));
    }
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}
