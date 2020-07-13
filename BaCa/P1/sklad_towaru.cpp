// Jakub Lukasiewicz

/* Abandon all hope, ye who enter here
 * As thou willn't been able to debug it */

#include <iostream>

// BC `<cstdint>` isn't allowed:
typedef unsigned char  uInt8;  // substitute of `uint8_t`
typedef unsigned short uInt16; // substitute of `uint16_t`

const uInt8  MAX_SIZE     = 128;
const uInt16 MAX_QUANTITY = 65535;

namespace storehouse_G { // calculating 'sum' of whole storehouse takes too long for BaCa
unsigned long long sum = 0;
}


struct Place {
    uInt16 quantity;
    uInt8  label     : 7;
    uInt8  isLabeled : 1;

    Place() : quantity(0), isLabeled(false) {}

    void setLabel(uInt8);
    void getLabel();
    void put(uInt16);
    void pop(uInt16);
    void mov(Place&, uInt16);  // moves amount from this 'place' to another
};

void Place::setLabel(uInt8 dd)
{
    label     = dd;
    isLabeled = true;
}

void Place::getLabel()
{
    if (isLabeled) {
        if (label < 10) { // alternatives: `cout.fill` + `cout.width` or `printf("%02d")`
            std::cout << "0" << (int)label << std::endl;
        }
        else {
            std::cout << (int)label << std::endl;
        }
    }
    else {
        std::cout << "--" << std::endl;
    }
}

void Place::put(uInt16 a)
{
    if (quantity + a > ::MAX_QUANTITY) {
        storehouse_G::sum += ::MAX_QUANTITY - quantity;
        quantity = ::MAX_QUANTITY;
    }
    else {
        storehouse_G::sum += a;
        quantity += a;
    }
}

void Place::pop(uInt16 a)
{
    if (a > quantity) {
        storehouse_G::sum -= quantity;
        quantity = 0;
    }
    else {
        storehouse_G::sum -= a;
        quantity -= a;
    }
}

void Place::mov(Place& dest, uInt16 a)
{
    if (a > quantity) {
        a = quantity;
    }
    if (dest.quantity + a > ::MAX_QUANTITY) {
        a = ::MAX_QUANTITY - dest.quantity;
    }

    quantity -= a;
    dest.quantity += a;
}


struct Shelf {
    uInt8 size;
    Place places[::MAX_SIZE];

    Shelf() : size(0) {}

    void set(uInt8);
    int get();
};

void Shelf::set(uInt8 p)
{
    for (uInt8 i = size; i < p; ++i) {
        storehouse_G::sum -= places[i].quantity;
        places[i].quantity = places[i].isLabeled = 0;
    }

    for (uInt8 i = p; i < size; ++i) {
        storehouse_G::sum -= places[i].quantity;
        places[i].quantity = places[i].isLabeled = 0;
    }

    size = p;
}

int Shelf::get()
{
    unsigned int sum = 0;
    for (uInt8 i = 0; i < size; ++i) {
        sum += places[i].quantity;
    }
    return sum;
}


struct Rack {
    uInt8 size;
    Shelf shelfs[::MAX_SIZE];

    Rack() : size(0) {}

    void set(uInt8, uInt8);
    int get();
};

void Rack::set(uInt8 s, uInt8 p)
{
    for (uInt8 i = 0; i < s; ++i) {
        shelfs[i].set(p);
    }
    for (uInt8 i = s; i < size; ++i) {
        shelfs[i].set(0);
    }
    size = s;
}

int Rack::get()
{
    unsigned int sum = 0;
    for (uInt8 i = 0; i < size; ++i) {
        sum += shelfs[i].get();
    }
    return sum;
}


struct Warehouse {
    uInt8 size;
    Rack racks[::MAX_SIZE];

    Shelf handyShelf;

    Warehouse() : size(0) {}

    void set(uInt8, uInt8, uInt8);
    unsigned long long get();
};

void Warehouse::set(uInt8 r, uInt8 s, uInt8 p)
{
    for (uInt8 i = 0; i < r; ++i) {
        racks[i].set(s, p);
    }
    for (uInt8 i = r; i < size; ++i) {
        racks[i].set(0, 0);
    }
    size = r;
}

unsigned long long Warehouse::get()
{
    unsigned long long sum = 0;
    for (uInt8 i = 0; i < size; ++i) {
        sum += racks[i].get();
    }
    sum += handyShelf.get();
    return sum;
}


struct Storehouse {
    uInt8 size;
    Warehouse warehouses[::MAX_SIZE];

    Rack handyRack;
    Shelf handyShelf;

    Storehouse() : size(0) {}

    void set(uInt8, uInt8, uInt8, uInt8);
    unsigned long long get();
    void fill(uInt8, uInt8, uInt8, uInt8, uInt16);

    bool readData(uInt16*, uInt16*, uInt16*, uInt16*, unsigned int*, uInt16*, uInt16*, uInt16*, uInt16*);

  private:
    bool validateData(uInt16*, uInt16*, uInt16*, uInt16*);
};

void Storehouse::set(uInt8 w, uInt8 r, uInt8 s, uInt8 p)
{
    for (uInt8 i = 0; i < w; ++i) {
        warehouses[i].set(r, s, p);
    }
    for (uInt8 i = w; i < size; ++i) {
        warehouses[i].set(0, 0, 0);
    }
    size = w;
}

unsigned long long Storehouse::get()
{
    return storehouse_G::sum;
}

void Storehouse::fill(uInt8 w, uInt8 r, uInt8 s, uInt8 p, uInt16 a)
{
    if (a > ::MAX_QUANTITY) {
        a = ::MAX_QUANTITY;
    }

    size = w;
    for (uInt8 i = 0; i < w; ++i) {
        warehouses[i].size = r;

        for (uInt8 j = 0; j < r; ++j) {
            warehouses[i].racks[j].size = s;
            for (uInt8 k = 0; k < s; ++k) {
                warehouses[i].racks[j].shelfs[k].size = p;
                for (uInt8 l = 0; l < p; ++l) {
                    warehouses[i].racks[j].shelfs[k].places[l].quantity = a;
                    warehouses[i].racks[j].shelfs[k].places[l].isLabeled = 0;
                }
            }
        }

        warehouses[i].handyShelf.size = p;
        for (uInt8 l = 0; l < p; ++l) {
            warehouses[i].handyShelf.places[l].quantity = a;
            warehouses[i].handyShelf.places[l].isLabeled = 0;
        }
    }

    handyRack.size = s;
    for (uInt8 k = 0; k < s; ++k) {
        handyRack.shelfs[k].size = p;
        for (uInt8 l = 0; l < p; ++l) {
            handyRack.shelfs[k].places[l].quantity = a;
            handyRack.shelfs[k].places[l].isLabeled = 0;
        }
    }

    handyShelf.size = p;
    for (uInt8 l = 0; l < p; ++l) {
        handyShelf.places[l].quantity = a;
        handyShelf.places[l].isLabeled = 0;
    }

    storehouse_G::sum = (unsigned long long)w * r * s * p * a + (unsigned long long)w * p * a + (unsigned long long)s * p * a + (unsigned long long)p * a;
}

bool Storehouse::validateData(uInt16* W, uInt16* R, uInt16* S, uInt16* P)
{
    bool flag = true;

    // Spaghetti:
    if (W) {
        if (*W >= size) {
            flag = false;
        }
        else {
            if (S) {
                if (R) {
                    if (*R >= warehouses[*W].size) {
                        flag = false;
                    }
                    else {
                        if (*S >= warehouses[*W].racks[*R].size) {
                            flag = false;
                        }
                        else {
                            if (P && *P >= warehouses[*W].racks[*R].shelfs[*S].size) {
                                flag = false;
                            }
                        }
                    }
                }
                else {
                    flag = false;
                }
            }
            else {
                if (R && P) {
                    flag = false;
                }
                else if (R && *R >= warehouses[*W].size) {
                    flag = false;
                }
                else if (P && *P >= warehouses[*W].handyShelf.size) {
                    flag = false;
                }
            }
        }
    }
    else {
        if (S) {
            if (*S >= handyRack.size) {
                flag = false;
            }
            else {
                if (P && *P >= handyRack.shelfs[*S].size) {
                    flag = false;
                }
            }
        }
        else {
            if (P && *P >= handyShelf.size) {
                flag = false;
            }
        }
    }

    return flag;
}

// order: w, r, s, p, a, dd, w2, r2, s2
bool Storehouse::readData(uInt16* w = NULL, uInt16* r = NULL, uInt16* s = NULL,
    uInt16* p = NULL, unsigned int* a = NULL, uInt16* dd = NULL,
    uInt16* w2 = NULL, uInt16* r2 = NULL, uInt16* s2 = NULL)
{
    if (w) { std::cin >> *w; }
    if (r) { std::cin >> *r; }
    if (s) { std::cin >> *s; }
    if (w2) { std::cin >> *w2; }
    if (r2) { std::cin >> *r2; }
    if (s2) { std::cin >> *s2; }
    if (p) { std::cin >> *p; }
    if (dd) { std::cin >> *dd; }
    if (a) { std::cin >> *a; }

    bool flag = true;

    if ((w  && *w  >= ::MAX_SIZE) || (r  && *r  >= ::MAX_SIZE) || (s  && *s  >= ::MAX_SIZE) ||
        (w2 && *w2 >= ::MAX_SIZE) || (r2 && *r2 >= ::MAX_SIZE) || (s2 && *s2 >= ::MAX_SIZE) ||
        (p  && *p  >= ::MAX_SIZE) || (dd && *dd > 99) ) {
        flag = false;
    }
    else {
        flag = validateData(w, r, s, p);

        if (w2 || r2 || s2) {
            /* This should be there, but BaCa does not think so
             * flag = validateData(w2, r2, s2, p)
             */

            // But almost the exact copy of `validateData` is completely fine
            if (w2) {
                if (*w2 >= size) {
                    flag = false;
                }
                else {
                    if (s2) {
                        if (r2) {
                            if (*r2 >= warehouses[*w2].size) {
                                flag = false;
                            }
                            else {
                                if (*s2 >= warehouses[*w2].racks[*r2].size) {
                                    flag = false;
                                }
                                else {
                                    if (p && *p >= warehouses[*w2].racks[*r2].shelfs[*s2].size) {
                                        flag = false;
                                    }
                                }
                            }
                        }
                        else {
                            flag = false;
                        }
                    }
                    else {
                        if (r2 && p) {
                            flag = false;
                        }
                        else if (r2 && *r2 >= warehouses[*w2].size) {
                            flag = false;
                        }
                        else if (p && *p >= warehouses[*w2].handyShelf.size) {
                            flag = false;
                        }
                    }
                }
            }
            else {
                if (s2) {
                    if (*s2 >= handyRack.size) {
                        flag = false;
                    }
                    else {
                        if (p && *p >= handyRack.shelfs[*s2].size) {
                            flag = false;
                        }
                    }
                }
                else {
                    if (p && *p >= handyShelf.size) {
                        flag = false;
                    }
                }
            }

        }
    }

    if (a && *a > ::MAX_QUANTITY) {
        *a = ::MAX_QUANTITY;
    }

    if (!flag) {
        std::cout << "error" << std::endl;
    }

    return flag;
}


int main()
{
    static Storehouse storehouse;

    std::string command, prefix;
    char x;
    uInt16 w, r, s, p, dd;
    uInt16 w2, r2, s2;
    unsigned int a;

    do {
        std::cin >> command;
        prefix = command.substr(0, 4);

        x = command[4];

        // Spaghetti:
        if (prefix == "SET-") {
            if (x == 'A') { // SET-A
                std::cin >> w >> r >> s >> p;
                if (w > ::MAX_SIZE || s > ::MAX_SIZE || r > ::MAX_SIZE || p > ::MAX_SIZE) {
                    std::cout << "error" << std::endl;
                }
                else {
                    x = command[5];
                    if (x == 'P') {
                        if (w < storehouse.size && r < storehouse.warehouses[w].size && s < storehouse.warehouses[w].racks[r].size) {
                            storehouse.warehouses[w].racks[r].shelfs[s].set(p);
                        }
                        else {
                            std::cout << "error" << std::endl;
                        }
                    }
                    else if (x == 'S') {
                        if (w < storehouse.size && r < storehouse.warehouses[w].size) {
                            storehouse.warehouses[w].racks[r].set(s, p);
                        }
                        else {
                            std::cout << "error" << std::endl;
                        }
                    }
                    else if (x == 'R') {
                        if (w < storehouse.size) {
                            storehouse.warehouses[w].set(r, s, p);
                        }
                        else {
                            std::cout << "error" << std::endl;
                        }
                    }
                    else if (x == 'W') {
                        storehouse.set(w, r, s, p);
                    }
                }
            }
            else if (x == 'H') {   // SET-H
                x = command[5];
                if (x == 'W') {
                    std::cin >> w >> p;
                    if (w >= storehouse.size || p > ::MAX_SIZE) {
                        std::cout << "error" << std::endl;
                    }
                    else {
                        storehouse.warehouses[w].handyShelf.set(p);
                    }
                }
                else if (x == 'R') {
                    std::cin >> s >> p;
                    if (s > ::MAX_SIZE || p > ::MAX_SIZE) {
                        std::cout << "error" << std::endl;
                    }
                    else {
                        storehouse.handyRack.set(s, p);
                    }
                }
                else if (x == 'S') {
                    std::cin >> p;
                    if (p > ::MAX_SIZE) {
                        std::cout << "error" << std::endl;
                    }
                    else {
                        storehouse.handyShelf.set(p);
                    }
                }
            }
            else if (x == 'L') {   // SET-L
                x = command[5];
                if (x == 'W') {
                    if (storehouse.readData(&w, &r, &s, &p, 0, &dd)) {
                        storehouse.warehouses[w].racks[r].shelfs[s].places[p].setLabel(dd);
                    }
                }
                else if (x == 'H') {
                    if (storehouse.readData(&w, 0, 0, &p, 0, &dd)) {
                        storehouse.warehouses[w].handyShelf.places[p].setLabel(dd);
                    }
                }
                else if (x == 'R') {
                    if (storehouse.readData(0, 0, &s, &p, 0, &dd)) {
                        storehouse.handyRack.shelfs[s].places[p].setLabel(dd);
                    }
                }
                else if (x == 'S') {
                    if (storehouse.readData(0, 0, 0, &p, 0, &dd)) {
                        storehouse.handyShelf.places[p].setLabel(dd);
                    }
                }
            }
        }
        else if (prefix == "PUT-") {
            x = command[4];
            if (x == 'W') {
                if (storehouse.readData(&w, &r, &s, &p, &a)) {
                    storehouse.warehouses[w].racks[r].shelfs[s].places[p].put(a);
                }
            }
            else if (x == 'H') {
                if (storehouse.readData(&w, 0, 0, &p, &a)) {
                    storehouse.warehouses[w].handyShelf.places[p].put(a);
                }
            }
            else if (x == 'R') {
                if (storehouse.readData(0, 0, &s, &p, &a)) {
                    storehouse.handyRack.shelfs[s].places[p].put(a);
                }
            }
            else if (x == 'S') {
                if (storehouse.readData(0, 0, 0, &p, &a)) {
                    storehouse.handyShelf.places[p].put(a);
                }
            }
        }
        else if (prefix == "FILL") {
            std::cin >> w >> r >> s >> p >> a;
            if (w > ::MAX_SIZE || r > ::MAX_SIZE || s > ::MAX_SIZE || p > ::MAX_SIZE) {
                std::cout << "error" << std::endl;
            }
            else {
                storehouse.fill(w, r, s, p, a);
            }
        }
        else if (prefix == "POP-") {
            x = command[4];
            if (x == 'W') {
                if (storehouse.readData(&w, &r, &s, &p, &a)) {
                    storehouse.warehouses[w].racks[r].shelfs[s].places[p].pop(a);
                }
            }
            else if (x == 'H') {
                if (storehouse.readData(&w, 0, 0, &p, &a)) {
                    storehouse.warehouses[w].handyShelf.places[p].pop(a);
                }
            }
            else if (x == 'R') {
                if (storehouse.readData(0, 0, &s, &p, &a)) {
                    storehouse.handyRack.shelfs[s].places[p].pop(a);
                }
            }
            else if (x == 'S') {
                if (storehouse.readData(0, 0, 0, &p, &a)) {
                    storehouse.handyShelf.places[p].pop(a);
                }
            }
        }
        else if (prefix == "MOV-") {
            x = command[4];
            if (x == 'W') {
                if (storehouse.readData(&w, &r, &s, &p, &a, 0, &w2, &r2, &s2)) {
                    storehouse.warehouses[w].racks[r].shelfs[s].places[p].mov(storehouse.warehouses[w2].racks[r2].shelfs[s2].places[p], a);
                }
            }
            else if (x == 'H') {
                if (storehouse.readData(&w, &r, &s, &p, &a)) {
                    storehouse.warehouses[w].racks[r].shelfs[s].places[p].mov(storehouse.warehouses[w].handyShelf.places[p], a);
                }
            }
            else if (x == 'R') {
                if (storehouse.readData(&w, &r, &s, &p, &a, 0, 0, 0, &s2)) {
                    storehouse.warehouses[w].racks[r].shelfs[s].places[p].mov(storehouse.handyRack.shelfs[s2].places[p], a);
                }
            }
            else if (x == 'S') {
                if (storehouse.readData(0, 0, &s, &p, &a)) {
                    storehouse.handyRack.shelfs[s].places[p].mov(storehouse.handyShelf.places[p], a);
                }
            }
        }
        else if (prefix == "GET-") {
            x = command[4];
            if (x == 'E') { // GET-E
                std::cout << storehouse.get() << std::endl;
            }
            else if (x == 'W') {   // GET-W
                if (storehouse.readData(&w)) {
                    std::cout << storehouse.warehouses[w].get() << std::endl;
                }
            }
            else if (x == 'R') {   // GET-R*
                x = command[5];
                if (x == 'W') {
                    if (storehouse.readData(&w, &r)) {
                        std::cout << storehouse.warehouses[w].racks[r].get() << std::endl;
                    }
                }
                else if (x == 'H') {
                    std::cout << storehouse.handyRack.get() << std::endl;
                }
            }
            else if (x == 'S') {   // GET-S*
                if (command == "GET-S") {
                    std::cout << storehouse.handyShelf.get() << std::endl;
                }
                else {
                    x = command[5];
                    if (x == 'W') {
                        if (storehouse.readData(&w, &r, &s)) {
                            std::cout << storehouse.warehouses[w].racks[r].shelfs[s].get() << std::endl;
                        }
                    }
                    else if (x == 'H') {
                        if (storehouse.readData(&w)) {
                            std::cout << storehouse.warehouses[w].handyShelf.get() << std::endl;
                        }
                    }
                    else if (x == 'R') {
                        if (storehouse.readData(0, 0, &s)) {
                            std::cout << storehouse.handyRack.shelfs[s].get() << std::endl;
                        }
                    }
                }
            }
            else if (x == 'L') {   // GET-L*
                x = command[5];
                if (x == 'W') {
                    if (storehouse.readData(&w, &r, &s, &p)) {
                        storehouse.warehouses[w].racks[r].shelfs[s].places[p].getLabel();
                    }
                }
                else if (x == 'H') {
                    if (storehouse.readData(&w, 0, 0, &p)) {
                        storehouse.warehouses[w].handyShelf.places[p].getLabel();
                    }
                }
                else if (x == 'R') {
                    if (storehouse.readData(0, 0, &s, &p)) {
                        storehouse.handyRack.shelfs[s].places[p].getLabel();
                    }
                }
                else if (x == 'S') {
                    if (storehouse.readData(0, 0, 0, &p)) {
                        storehouse.handyShelf.places[p].getLabel();
                    }
                }
            }
        }

    } while (command != "END");

    return 0;
}

// vim: fen
