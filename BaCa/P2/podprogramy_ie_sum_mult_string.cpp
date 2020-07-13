// Jakub Lukasiewicz

std::string Sum(int, const std::string[]);
std::string Sum(int, ...);
void Sum(std::string*, int, const std::string[]);
void Sum(std::string*, int, ...);
void Sum(std::string&, int, const std::string[]);
void Sum(std::string&, int, ...);

std::string Mult(int, const std::string[]);
std::string Mult(int, ...);
void Mult(std::string*, int, const std::string[]);
void Mult(std::string*, int, ...);
void Mult(std::string&, int, const std::string[]);
void Mult(std::string&, int, ...);

std::string Operation(std::string (*)(int, const std::string*), int, const std::string[]);
std::string Operation(std::string (*)(int, const std::string*), int, ...);
void Operation(std::string*, std::string (*)(int, const std::string*), int, const std::string[]);
void Operation(std::string*, std::string (*)(int, const std::string*), int, ...);
void Operation(std::string&, void (*)(int, const std::string*), int, const std::string[]);
void Operation(std::string&, void (*)(int, const std::string*), int, ...);

namespace operations {

std::string reverse(const std::string&, size_t = 0);
std::string trim0(const std::string&, size_t = 0);
short cmp(const std::string&, const std::string&, size_t);
short cmp(const std::string&, const std::string&);
std::string add(const std::string&, const std::string&, bool = 0, size_t = 0);
std::string sub(const std::string&, const std::string&, bool = 0, size_t = 0);
std::string sum(std::string, std::string);
std::string multi(const std::string& a, const char& b, char c = 0, size_t n = 0);
std::string multi(const std::string&, const std::string&, std::string = "", size_t = 0);
std::string mult(std::string, std::string);

std::string reverse(const std::string& x, size_t n)
{
    if (n < x.length()) {
        std::string temp = "";
        temp += *(x.rbegin()+n);
        return temp + reverse(x, n+1);
    }
    else {
        return "";
    }
}

std::string trim0(const std::string& x, size_t n)
{
    if (n < x.length()-1 && x[n] == '0') {
        return trim0(x, n+1);
    }
    else {
        return x.substr(n, x.length());
    }
}

short cmp(const std::string& a, const std::string& b, size_t n)
{
    if (a[n] > b[n]) {
        return 1;
    }
    else if (a[n] < b[n]) {
        return -1;
    }
    else {
        return cmp(a,b,n+1);
    }
}

short cmp(const std::string& a, const std::string& b)
{
    if (a == b) {
        return 0;
    }
    else if (a.length() > b.length()) {
        return 1;
    }
    else if (a.length() < b.length()) {
        return -1;
    }
    else {
        return cmp(a,b,0);
    }
}

std::string add(const std::string& a, const std::string& b, bool c, size_t n)
{
    if ((n < a.length() && n < b.length()) || c != 0) {
        std::string temp = "";
        char x = c;
        x += n < a.length() ? (*(a.rbegin()+n) - '0') : 0;
        x += n < b.length() ? (*(b.rbegin()+n) - '0') : 0;
        if (x > 9) {
            x -= 10;
            c = 1;
        }
        else {
            c = 0;
        }
        temp += x + '0';
        temp += add(a, b, c, n+1);
        return n == 0 ? reverse(temp) : temp;
    }
    else if (n < a.length()) {
        return reverse(a.substr(0, a.length() - n));
    }
    else if (n < b.length()) {
        return reverse(b.substr(0, b.length() - n));
    }
    else {
        return "";
    }
}

std::string sub(const std::string& a, const std::string& b, bool c, size_t n)
{
    if (n < b.length() || c != 0) {
        std::string temp = "";
        char x = (*(a.rbegin()+n) - '0') - c;
        x -= n < b.length() ? (*(b.rbegin()+n) - '0') : 0;
        if (x < 0) {
            x += 10;
            c = 1;
        }
        else {
            c = 0;
        }
        temp += x + '0';
        temp += sub(a, b, c, n+1);
        return n == 0 ? reverse(temp) : temp;
    }
    else if (n < a.length()) {
        return reverse(a.substr(0, a.length() - n));
    }
    else {
        return "";
    }
}

std::string sum(std::string a, std::string b)
{
    bool neg_a = (a[0] == '-');
    bool neg_b = (b[0] == '-');

    if (neg_a || a[0] == '+') {
        a = a.substr(1, a.length());
    }

    if (neg_b || b[0] == '+') {
        b = b.substr(1, b.length());
    }

    a = trim0(a);
    b = trim0(b);

    short comp = cmp(a, b);

    if (a == "0" && b == "0") {
        return "0";
    }
    else if (a == "0") {
        return neg_b ? "-" + b : b;
    }
    else if (b == "0") {
        return neg_a ? "-" + a : a;
    }
    else if (neg_a && neg_b) {
        return "-" + add(a,b);
    }
    else if ((neg_a || neg_b) && comp == 0) {
        return "0";
    }
    else if (neg_a) {
        std::string temp = comp == 1 ? sub(a,b) : sub(b,a);
        temp = trim0(temp);
        return comp == 1 ? "-" + temp : temp;
    }
    else if (neg_b) {
        std::string temp = comp == -1 ? sub(b,a) : sub(a,b);
        temp = trim0(temp);
        return comp == -1 ? "-" + temp : temp;
    }
    else {
        return add(a,b);
    }
}

std::string multi(const std::string& a, const char& b, char c, size_t n)
{
    if (n < a.length() || c != 0) {
        char x = c;
        x += n < a.length() ? (*(a.rbegin()+n) - '0') * (b - '0') : 0;
        std::string temp = "";
        temp += x%10 + '0';
        temp += multi(a, b, x/10, n+1);
        return n == 0 ? reverse(temp) : temp;
    }
    else {
        return "";
    }
}

std::string multi(const std::string& a, const std::string& b, std::string c, size_t n)
{
    if (n < b.length()) {
        return add(multi(a, *(b.rbegin()+n)) + c, multi(a, b, c + "0", n+1));
    }
    else {
        return "0";
    }
}

std::string mult(std::string a, std::string b)
{
    bool neg_a = (a[0] == '-');
    bool neg_b = (b[0] == '-');

    if (neg_a || a[0] == '+') {
        a = a.substr(1, a.length());
    }

    if (neg_b || b[0] == '+') {
        b = b.substr(1, b.length());
    }

    a = trim0(a);
    b = trim0(b);

    if (a == "0" || b == "0") {
        return "0";
    }
    else if (neg_a != neg_b) {
        return "-" + multi(a, b);
    }
    else {
        return multi(a,b);
    }
}

}

namespace helpers {

std::string sum(int n, int N, std::va_list args)
{
    if (n < N) {
        std::string temp = va_arg(args, char*);
        return operations::sum(temp, sum(n+1, N, args));
    }
    else {
        return "0";
    }
}

std::string mult(int n, int N, std::va_list args)
{
    if (n < N) {
        std::string temp = va_arg(args, char*);
        return operations::mult(temp, mult(n+1, N, args));
    }
    else {
        return "1";
    }
}

std::string Sum(int N, const std::string d[], int n)
{
    if (n < N) {
        return operations::sum(d[n], Sum(N, d, n+1));
    }
    else {
        return "0";
    }
}

std::string Mult(int N, const std::string d[], int n)
{
    if (n < N) {
        return operations::mult(d[n], Mult(N, d, n+1));
    }
    else {
        return "1";
    }
}

void arrayify(int n, int N, std::string d[], std::va_list args)
{
    if (n < N) {
        d[n] = static_cast<std::string>(va_arg(args, char*));
        arrayify(n+1, N, d, args);
    }
}

}

std::string Sum(int N, const std::string d[])
{
    return helpers::Sum(N, d, 0);
}

std::string Sum(int N, ...)
{
    std::va_list args;
    va_start(args, N);
    std::string r = helpers::sum(0, N, args);
    va_end(args);
    return r;
}

void Sum(std::string* r, int N, const std::string d[])
{
    *r = helpers::Sum(N, d, 0);
}

void Sum(std::string* r, int N, ...)
{
    std::va_list args;
    va_start(args, N);
    *r = helpers::sum(0, N, args);
    va_end(args);
}

void Sum(std::string& r, int N, const std::string d[])
{
    r = helpers::Sum(N, d, 0);
}

void Sum(std::string& r, int N, ...)
{
    std::va_list args;
    va_start(args, N);
    r = helpers::sum(0, N, args);
    va_end(args);
}


std::string Mult(int N, const std::string d[])
{
    return helpers::Mult(N, d, 0);
}

std::string Mult(int N, ...)
{
    std::va_list args;
    va_start(args, N);
    std::string r = helpers::mult(0, N, args);
    va_end(args);
    return r;
}

void Mult(std::string* r, int N, const std::string d[])
{
    *r = helpers::Mult(N, d, 0);
}

void Mult(std::string* r, int N, ...)
{
    std::va_list args;
    va_start(args, N);
    *r = helpers::mult(0, N, args);
    va_end(args);
}

void Mult(std::string& r, int N, const std::string d[])
{
    r = helpers::Mult(N, d, 0);
}

void Mult(std::string& r, int N, ...)
{
    std::va_list args;
    va_start(args, N);
    r = helpers::mult(0, N, args);
    va_end(args);
}


std::string Operation(std::string (*f)(int, const std::string*), int N, const std::string d[])
{
    return f(N, d);
}

std::string Operation(std::string (*f)(int, const std::string*), int N, ...)
{
    std::string* d = new std::string[N];
    std::va_list args;
    va_start(args, N);
    helpers::arrayify(0, N, d, args);
    va_end(args);
    std::string r = f(N, d);
    delete [] d;
    return r;
}

void Operation(std::string* r, std::string (*f)(int, const std::string*), int N, const std::string d[])
{
    *r = f(N, d);
}

void Operation(std::string* r, std::string (*f)(int, const std::string*), int N, ...)
{
    std::string* d = new std::string[N];
    std::va_list args;
    va_start(args, N);
    helpers::arrayify(0, N, d, args);
    va_end(args);
    *r = f(N, d);
    delete [] d;
}

void Operation(std::string& r, void (*f)(std::string*, int, const std::string*), int N, const std::string d[])
{
    f(&r, N, d);
}

void Operation(std::string& r, void (*f)(std::string*, int, const std::string*), int N, ...)
{
    std::string* d = new std::string[N];
    std::va_list args;
    va_start(args, N);
    helpers::arrayify(0, N, d, args);
    va_end(args);
    f(&r, N, d);
    delete [] d;
}


// vim: fen
