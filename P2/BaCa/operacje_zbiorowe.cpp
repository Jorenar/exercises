// Jakub Lukasiewicz

// # prototypes # {{{

// Main functions
void Emplace(std::string, int*);
void Insert(std::string, int*);
void Erase(std::string, int*);
void Print(int, std::string*);
bool Emptiess(int);
bool Nonempty(int);
bool Member(std::string, int);
bool Disjoint(int, int);
bool Conjunctive(int, int);
bool Equality(int, int);
bool Inclusion(int, int);
void Union(int, int, int*);
void Intersection(int, int, int*);
void Symettric(int, int, int*);
void Difference(int, int, int*);
void Complement(int, int*);
bool LessThen(int, int*);
bool LessEqual(int, int);
bool GreatEqual(int, int);
bool GreatThen(int, int);

// Helpers
int sum(int, int);
int cardinality(int, int = 0);
int parse(std::string, int*);

// prototypes }}}

// # helpers # {{{

int sum(int x, int y)
{
    if (y == 0) {
        return x;
    }
    else {
        return sum(x ^ y, (x & y) << 1);
    }
}

int cardinality(int set, int i)
{
    if (i < 32) {
        if (set & (1 << i)) {
            return sum(cardinality(set, sum(i, 1)), 1);
        }
        return cardinality(set, sum(i, 1));
    }
    return 0;
}

int parse(std::string input, int& i)
{
    int x = 1;

    if (input.at(i) == '1') { x <<= 16; }
    i = sum(i, 1);

    if (input.at(i) == '1') { x <<= 8; }
    i = sum(i, 1);

    if (input.at(i) == '1') { x <<= 4; }
    i = sum(i, 1);

    if (input.at(i) == '1') { x <<= 2; }
    i = sum(i, 1);

    if (input.at(i) == '1') { x <<= 1; }

    return x;
}

// helpers }}}

// # functions # {{{

void Emplace(std::string input, int* set)
{
    *set = 0;
    Insert(input, set);
}

void Insert(std::string input, int* set)
{
    static int i = 0;
    if (i < input.length()) {
        if (input.at(i) == '0' || input.at(i) == '1') {
            *set |= parse(input, i);
        }
        i = sum(i, 1);
        Insert(input, set);
    }
    else {
        i = 0;
    }
}

void Erase(std::string input, int* set)
{
    static int i = 0;
    if (i < input.length()) {
        if ( input.at(i) == '0' ||  input.at(i) == '1' ) {
            *set &= ~(parse(input, i));
        }
        i = sum(i, 1);
        Erase(input, set);
    }
    else {
        i = 0;
    }
}

void Print(int set, std::string* output)
{
    static int i = 31;
    if (i < 0) {
        i = 31;
    }
    else if (set == 0) {
        i = 31;
        *output = "empty";
    }
    else {
        if (i == 31) {
            *output = "";
        }

        if (set & (1 << i)) {
            std::stringstream ss;
            ss << *output;
            ss  << (i / 16)
                << (i / 8 ) % 2
                << (i / 4 ) % 4 % 2
                << (i / 2 ) % 8 % 2
                << (i % 2 )
                << " ";
            *output = ss.str();
        }

        i = sum(i, sum(1, ~1));
        Print(set, output);
    }
}

bool Emptiness(int set)
{
    return set == 0;
}

bool Nonempty(int set)
{
    return set != 0;
}

bool Member(std::string input, int set)
{
    static int i = 0;
    if (i < input.length()) {
        if (input.at(i) == '0' || input.at(i) == '1') {
            int x = parse(input, i);
            i = 0;
            return (set & x);
        }
        i = sum(i, 1);
        return Member(input, set);
    }
    else {
        i = 0;
        return false;
    }
}

bool Disjoint(int A, int B)
{
    return (A & B) == 0;
}

bool Conjunctive(int A, int B)
{
    return (A & B) != 0;
}

bool Equality(int A, int B)
{
    return A == B;
}

bool Inclusion(int A, int B)
{
    return (A | B) == B;
}

void Union(int A, int B, int* output)
{
    *output = A | B;
}

void Intersection(int A, int B, int* output)
{
    *output = A & B;
}

void Symmetric(int A, int B, int* output)
{
    *output = (A ^ B);
}

void Difference(int A, int B, int* output)
{
    *output = (A & (~B));
}

void Complement(int set, int* output)
{
    *output = (~set);
}

bool LessThen(int A, int B)
{
    int a = cardinality(A);
    int b = cardinality(B);
    return ((a < b) || (a == b && (unsigned)A < (unsigned)B));
}

bool LessEqual(int A, int B)
{
    int a = cardinality(A);
    int b = cardinality(B);
    return ((a < b) || (a == b && (unsigned)A <= (unsigned)B));
}

bool GreatEqual(int A, int B)
{
    return !LessThen(A, B);
}

bool GreatThen(int A, int B)
{
    return !LessEqual(A, B);
}

// functions }}}

// vim: fen
