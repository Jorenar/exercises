#include "clients.hpp"

#include "util.hpp"
#include "ansi_esc_seq.h"
#include <readline/readline.h>

Clients::Clients(sqlite3* db) : Base(db, "Clients", "SELECT * FROM clients_view")
{
    readRecords<Record>();

    tp.AddColumn("Name ", 25);
    tp.AddColumn("Phone number ", 15);
    tp.AddColumn("Email ", 30);
    tp.AddColumn("Orders", 6);
}

Clients::Record::Record(sqlite3_stmt* stmt)
{
    id      = sqlite3_column_int(stmt, 0);
    name    = uCharToStr(sqlite3_column_text(stmt, 1));
    surname = uCharToStr(sqlite3_column_text(stmt, 2));
    tel     = uCharToStr(sqlite3_column_text(stmt, 3));
    email   = uCharToStr(sqlite3_column_text(stmt, 4));
    orders  = sqlite3_column_int(stmt, 5);
}

void Clients::Record::print(bprinter::TablePrinter& out) const
{
    out << name + " " + surname + " "
        << tel + " "
        << email + " "
        << orders;
}

void Clients::Record::detailed() const
{
    std::cout
        << "----------"
        << " Client details "
        << "----------"
        << "\n\n";

    std::cout
        << "Name:          " << name    << "\n"
        << "Surname:       " << surname << "\n"
        << "Phone number:  " << tel     << "\n"
        << "Email:         " << email   << "\n"
        << "Placed orders: " << orders  << "\n";

    std::cout << "\n" << "(e)dit  (q)uit" << std::endl;
}

void Clients::Record::edit()
{
    std::cout << "\n";

    std::string temp_name    = Readline("  % First name:   ", name);
    std::string temp_surname = Readline("  % Last name:    ", surname);
    std::string temp_tel     = Readline("  % Phone number: ", tel);
    std::string temp_email   = Readline("  % Email:        ", email);

    std::string r = Readline("Save? [Y/n] ", "");
    if (r == "" || r == "y" || r == "yes") {
        name    = temp_name;
        surname = temp_surname;
        tel     = temp_tel;
        email   = temp_email;
    }
}
