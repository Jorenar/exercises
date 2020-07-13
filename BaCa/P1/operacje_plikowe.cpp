// Jakub Lukasiewicz

namespace input {

template<typename T1, typename T2>
    inline T1& cast(T2& x) { return *((T1*)&(x)); }

}

struct Record {
  public:
    int n;
    std::string str {""};
    std::string ch; // array, because spaces also are in data files, so `getline` is needed

  private:
    struct Set {
        bool tf;
        unsigned char uch;
        float fl;

        bool operator ==(const Set set)
        {
            return this->tf == set.tf && this->uch == set.uch && this->fl == set.fl;
        }
    };

  public:
    Set set0;
    Set set1;
    Set set2;
    Set set3;

    int sum();

    bool operator ==(const Record);

    friend std::istream& operator >>(std::istream&, Record&);
    friend std::ostream& operator <<(std::ostream&, const Record);
};

int Record::sum()
{
    return (set0.uch + set1.uch + set2.uch + set3.uch) % 256;
}

bool Record::operator ==(const Record data)
{
    return
        this->n    == data.n    &&
        this->str  == data.str  &&
        this->ch   == data.ch   &&
        this->set0 == data.set0 &&
        this->set1 == data.set1 &&
        this->set2 == data.set2 &&
        this->set3 == data.set3;
}

std::istream& operator >>(std::istream& in, Record& data)
{
    in >> data.n;
    in.ignore(2, '\n'); // ignore \n after int data field
    std::getline(in, data.str);
    std::getline(in, data.ch);
    in  >> data.set0.tf >> input::cast<int>(data.set0.uch) >> data.set0.fl
        >> data.set1.tf >> input::cast<int>(data.set1.uch) >> data.set1.fl
        >> data.set2.tf >> input::cast<int>(data.set2.uch) >> data.set2.fl
        >> data.set3.tf >> input::cast<int>(data.set3.uch) >> data.set3.fl;
    return in;
}

std::ostream& operator <<(std::ostream& out, const Record data)
{
    return out
        << data.n       << '\n'
        << data.str     << '\n'
        << data.ch      << '\n'
        << data.set0.tf << ' ' << static_cast<int>(data.set0.uch) << ' ' << data.set0.fl << '\n'
        << data.set1.tf << ' ' << static_cast<int>(data.set1.uch) << ' ' << data.set1.fl << '\n'
        << data.set2.tf << ' ' << static_cast<int>(data.set2.uch) << ' ' << data.set2.fl << '\n'
        << data.set3.tf << ' ' << static_cast<int>(data.set3.uch) << ' ' << data.set3.fl << '\n';
}

struct Digi {
    int N;
    int n;
    std::string str; // just for compability with file_management::SortData

    friend std::istream& operator >>(std::istream& in, Digi& data)
    {
        in >> data.N >> data.n;
        return in;
    }

    friend std::ostream& operator <<(std::ostream& out, const Digi data)
    {
        return out << data.N << " " << data.n << std::endl;
    }
};

namespace file_management {

void cp(const std::string source, const std::string destination)
{
    std::ifstream src(source.c_str());
    std::ofstream dst(destination.c_str());
    std::string buf;
    while (std::getline(src, buf)) {
        dst << buf << '\n';
    }
    src.close();
    dst.close();
}

template<typename T>
void SortData(const std::string path0, const std::string path1, const short checkMode)
{
    bool wasSwap;
    T data;
    T companion;

    std::ifstream file;
    std::ofstream helper;

    do {
        wasSwap = false;

        file.open(path0.c_str());
        helper.open(path1.c_str());

        if (file >> data) {
            while (file >> companion) {
                // lambdas instead of 'checkMode' would be so much more pleasant...
                if ((!checkMode && (data.n > companion.n)) ||
                    (checkMode > 0 && (data.str > companion.str)) ||
                    (checkMode < 0 && (data.n < companion.n))) {
                    helper << companion;
                    wasSwap = true;
                }
                else {
                    helper << data;
                    data = companion;
                }
            }

            helper << data;
        }

        file.close();
        helper.close();

        if (wasSwap) {
            file_management::cp(path1, path0);
        }

    } while (wasSwap);
}

}


void SortCount(std::string path0, std::string path1, std::string path2)
{
    file_management::SortData<Record>(path0, path1, -1);

    std::fstream file;
    file.open(path0.c_str(), std::fstream::in);

    Record data;

    if (file >> data) {
        std::fstream helper;
        std::fstream counter;

        counter.open(path2.c_str(), std::fstream::out | std::fstream::trunc);

        int count_n = 1;
        int num = data.n;
        while (file >> data) {
            if (data.n == num) {
                count_n++;
            }
            else {
                counter << num << " " << count_n << std::endl;
                num = data.n;
                count_n = 1;
            }
        }
        counter << num << " " << count_n << std::endl;
        counter.close();
        file.close();

        // "składową typu int o większej liczności"
        file_management::SortData<Digi>(path2, path1, -1);

        counter.open(path2.c_str(), std::fstream::in);
        helper.open(path1.c_str(), std::fstream::out | std::fstream::trunc);

        // 'count_n' is used just as dummy (like /dev/null)
        while (counter >> num >> count_n) {
            file.open(path0.c_str(), std::fstream::in);
            while (file >> data) {
                if (data.n == num) {
                    helper << data;
                }
            }
            file.close();
        }
        helper.close();
        counter.close();

        file_management::cp(path1, path0);

        Record companion;
        bool wasSwap;

        do {
            wasSwap = false;

            file.open(path0.c_str(), std::fstream::in);
            helper.open(path1.c_str(), std::fstream::out | std::fstream::trunc);

            if (file >> data) {
                while (file >> companion) {
                    // lambdas instead of 'checkMode' would be so much more pleasant...
                    if (data.n == companion.n && data.sum() < companion.sum()) {
                        helper << companion;
                        wasSwap = true;
                    }
                    else {
                        helper << data;
                        data = companion;
                    }
                }

                helper << data;
            }

            file.close();
            helper.close();

            if (wasSwap) {
                file_management::cp(path1, path0);
            }

        } while (wasSwap);
    }
    else {
        file.close();
    }
}

void SortInt(std::string path0, std::string path1, std::string)
{
    file_management::SortData<Record>(path0, path1, 0);
}

void SortString(std::string path0, std::string path1, std::string)
{
    file_management::SortData<Record>(path0, path1, 1);
}

/* There are two versions of SymmetricDifference:
 *     - (1) commented out
 *     - (2) "acitve"
 * Both utilize the same alghorithm
 * Version (1) is short, readable and beautiful, but BaCa doesn't approve
 *    (probably the same situation like with validateData() in "Skład towaru"
 * Version (2) is ugly, long, unreadable and nonstructural, but BaCa like it
 * I don't want to look at (2) anymore...
 */

/*
 * void SymmetricDifference(std::string path0, std::string path1, std::string path2)
 * {
 *     bool toTransfer;
 *
 *     std::fstream file0;
 *     std::fstream file1(path1.c_str(), std::fstream::in);
 *     std::fstream helper(path2.c_str(), std::fstream::out | std::fstream::trunc);
 *
 *     Record data;
 *     Record buffer;
 *
 *     while (file1 >> data) {
 *         toTransfer = true; // at start we assume read data is to be moved
 *
 *         file0.open(path0.c_str(), std::fstream::in);
 *         while (toTransfer && file0 >> buffer) {
 *             if (data == buffer) {
 *                 toTransfer = false;
 *             }
 *         } // when loop exist then either, because data isn't to be transferred
 *           // or the file ended and data wasn't in there (meaning it is to be transferred)
 *         file0.close();
 *
 *         if (toTransfer) {
 *             file0.open(path0.c_str(), std::fstream::app);
 *             file0 << data;
 *             file0.close();
 *         }
 *         else {
 *             helper << data; // in helper we keep the non transferred data
 *         }
 *     }
 *
 *     file1.close();
 *     helper.close();
 *
 *     file_management::cp(path2, path1);
 * }
 */

void SymmetricDifference( std::string path0, std::string path1, std::string path2 )
{
    std::fstream file0;
    std::fstream file1;
    std::fstream helper;

    bool toTransfer = false;
    std::string iLineIN,  sLineIN,  cLineIN,  rest1IN,  rest2IN,  rest3IN,  rest4IN;
    std::string iLineOUT, sLineOUT, cLineOUT, rest1OUT, rest2OUT, rest3OUT, rest4OUT;

    file1.open(path1.c_str(), std::fstream::in | std::fstream::ate);
    if (file1.tellg() == 0) {
        file1.close();
        return;
    }
    file1.close();

    file1.open(path1.c_str(), std::fstream::out | std::fstream::in);
    helper.open(path2.c_str(), std::fstream::out | std::fstream::in | std::fstream::trunc);

    while (true) {
        std::getline(file1, iLineIN);
        if (file1.eof()) { break; }
        std::getline(file1, sLineIN);
        std::getline(file1, cLineIN);

        std::getline(file1, rest1IN);
        std::getline(file1, rest2IN);
        std::getline(file1, rest3IN);
        std::getline(file1, rest4IN);

        toTransfer = true;
        file0.open(path0.c_str(), std::fstream::in);
        do {
            std::getline(file0, iLineOUT);
            if (file0.eof()) { break; }
            std::getline(file0, sLineOUT);
            std::getline(file0, cLineOUT);

            std::getline(file0, rest1OUT);
            std::getline(file0, rest2OUT);
            std::getline(file0, rest3OUT);
            std::getline(file0, rest4OUT);

            if (iLineIN == iLineOUT &&
                sLineIN == sLineOUT &&
                cLineIN == cLineOUT &&
                rest1IN == rest1OUT &&
                rest2IN == rest2OUT &&
                rest3IN == rest3OUT &&
                rest4IN == rest4OUT) {
                toTransfer = false;
                break;
            }
        } while ( true );
        file0.close();

        if (toTransfer) {
            file0.open(path0.c_str(), std::fstream::out | std::fstream::app);
            if (file0.tellg() != 0) {
                file0 << std::endl;
            }
            file0 << iLineIN << std::endl
                << sLineIN << std::endl
                << cLineIN << std::endl
                << rest1IN << std::endl
                << rest2IN << std::endl
                << rest3IN << std::endl
                << rest4IN;
            file0.close();
        }
        else {
            if (helper.tellg() != 0) {
                helper << std::endl;
            }
            helper << iLineIN << std::endl
                << sLineIN << std::endl
                << cLineIN << std::endl
                << rest1IN << std::endl
                << rest2IN << std::endl
                << rest3IN << std::endl
                << rest4IN;
        }
    }

    file1.close();
    helper.close();

    file1.open(path1.c_str(), std::fstream::out | std::fstream::trunc);
    helper.open(path2.c_str(), std::fstream::in);
    while (true) {
        std::getline(helper, iLineIN);
        if (helper.eof()) { break; }
        std::getline(helper, sLineIN);
        std::getline(helper, cLineIN);

        std::getline(helper, rest1IN);
        std::getline(helper, rest2IN);
        std::getline(helper, rest3IN);
        std::getline(helper, rest4IN);

        if (file1.tellg() != 0) {
            file1 << std::endl;
        }
        file1  << iLineIN << std::endl
            << sLineIN << std::endl
            << cLineIN << std::endl
            << rest1IN << std::endl
            << rest2IN << std::endl
            << rest3IN << std::endl
            << rest4IN;
    }

    file1.close();
    helper.close();
}

// vim: fen
