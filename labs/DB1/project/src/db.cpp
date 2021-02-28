#include "db.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>

#include <unistd.h>
#include <xdgdirs.h>

#include "util.hpp"

DB::DB()
{
    std::string db_path{};
    db_path += xdgDataHome();
    db_path += "/foo/foo.db";

    std::string schema{};

    if (!std::filesystem::exists(db_path)) {
        std::ifstream ifs("schema.sql"); // TODO: proper path to schema
        schema = std::string(std::istreambuf_iterator<char>(ifs),
                             std::istreambuf_iterator<char>());
    }

    if (sqlite3_open(db_path.c_str(), &handle)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(handle) << std::endl;
        sqlite3_close(handle);
        exit(1);
    }

    if (!schema.empty()) {
        exec(schema, NULL, NULL);
    }
}

DB::~DB()
{
    sqlite3_close(handle);
}

sqlite3* DB::raw()
{
    return handle;
}

void DB::exec(std::string query, int (* callback)(void*, int, char**, char**), void* foo)
{
    char* zErrMsg = 0;
    int rc = sqlite3_exec(handle, query.c_str(), callback, foo, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
}
