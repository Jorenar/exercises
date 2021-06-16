#pragma once

#include <string>
#include <sqlite3.h>

class DB {
    sqlite3* handle;
public:
    DB();
    ~DB();
    sqlite3* raw();
    void exec(std::string query, int (*callback)(void *, int, char **, char **), void*);
};
