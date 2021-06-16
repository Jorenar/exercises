#include "orders.hpp"

#include "util.hpp"

Orders::Orders(sqlite3* db) : Base(db, "Orders",
                                   "SELECT id, deviceID, clientID FROM orders")
{
    readRecords<Record>();

    tp.AddColumn("Client ID ", 25);
    tp.AddColumn("Device ID ", 15);
    tp.AddColumn("State ", 30);
}

Orders::Record::Record(sqlite3_stmt* stmt)
{
    id       = sqlite3_column_int(stmt, 0);
    deviceID = sqlite3_column_int(stmt, 1);
    clientID = sqlite3_column_int(stmt, 2);
    // state    = uCharToStr(sqlite3_column_text(stmt, 3));
}

void Orders::Record::print(bprinter::TablePrinter& out) const
{
    out << std::to_string(clientID) + " "
        << std::to_string(deviceID) + " "
        << state + " ";
}
