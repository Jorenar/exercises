#include "base.hpp"

#include <iostream>

#include "ansi_esc_seq.h"
#include "util.hpp"

std::vector<std::string> Base::tabs{};

Base::Base(sqlite3* db, std::string t, std::string query) :
    startline(0), db(db), tp(&std::cout), tab(t), current(0)
{
    tabs.push_back(t);

    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
}

void Base::next()
{
    if (current < size() - 1) {
        ++current;
        if (current >= startline + winRows() - 15) {
            ++startline;
        }
        this->print();
    }
}

void Base::prev()
{
    if (current > 0) {
        --current;
        if (current < startline) {
            --startline;
        }
        this->print();
    }
}

void Base::print()
{
    clear();

    for (auto& t: tabs) {
        if (t == tab) {
            std::cout << BG_RGB_SEQ(50,50,50);
        }
        std::cout << t << RESET << " ";
    }
    std::cout << "\n" << std::endl;

    tp.PrintHeader();

    int y = 0;
    int Y = winRows() - 5;
    for (std::size_t i = startline; y < Y && i < size(); ++i) {
        if (i == current) {
            std::cout << BG_RGB_SEQ(25,25,25);
        }

        records[i]->print(tp);

        std::cout << RESET;
        ++y;
    }

    tp.PrintFooter();

    std::cout << "\n" << "(q)uit" << std::endl;
}

std::size_t Base::size() const
{
    return records.size();
}

void Base::box()
{
    clear();
    records[current]->detailed();

    bool flag = true;
    while (flag) {
        switch (getch()) {
            case 'e':
                records[current]->edit();
                clear();
                records[current]->detailed();
                break;
            case 'q':
                flag = false;
                break;
        }
    }
}
