// Jakub Lukasiewicz

#include <string>

std::string FormatujNapis(std::string str,
    std::string str1, std::string str2, std::string str3)
{
    std::string proc_params[] = { str1, str2, str3 };
    char  c;
    int   k;
    short n;
    short m;
    short j;                // The size of formatting sequence
    std::string left  = ""; // Already formatted part of string
    std::string right = ""; // Optional part which is placed instead of formatting sequence
    std::string infix = ""; // Part to be yet formatted

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '{') {
            n = str[i+3] - '0';
            j = i + 5;
            switch (str[i+1]) {
                case 'p':
                    c = str[i+5];
                    infix = std::string(n, c);
                    j += 2;
                    break;
                case 'u':
                    while (n) {
                        while (str[j] == '{') {
                            k = 5;
                            if (str[j+1] == 'p') { k += 2; }
                            while (k--) {
                                right += str[j];
                                j++;
                            }
                        }
                        n--;
                        j++;
                    }
                    break;
                case 'U':
                    left.resize(left.size() - n);
                    i -= n;
                    break;
                case 'w':
                    infix = proc_params[n-1];
                    break;
                case 'W':
                    m = str[i+5] - '0';
                    infix = proc_params[n-1];
                    infix.resize(m, ' ');
                    j += 2;
                    break;
            }
            for (j; j < str.size(); ++j) {
                right += str[j];
            }
            str = left + infix + right;
            right = infix = "";
        }

        // Check if there is "}{"
        if (str[i] != '{') {
            left += str[i];
        }
        else { // because if there is, then decrement iterator
            i--;
        }
    }

    return str;
}

std::string NormalizujNapis(std::string str)
{
    std::string normalized = "";

    int i = 0;
    while (str[i] == ' ') { i++; } // Omit spaces at the beginning of the string

    for (i; i < str.size(); ++i) {
        // Change /\s*([\s\W])/ to /\1/
        while (str[i] == ' ' && (str[i+1] == ' ' || str[i+1] == '.' || str[i+1] == ',')) { i++; }

        normalized += str[i];

        // Add spaces after comas and dots (except the one at the end of sentence)
        if ((str[i] == '.' || str[i] == ',') && i < str.size() - 1 && str[i+1] != ' ') {
            normalized += ' ';
        }
    }

    // Remove space from the end of string
    if (normalized[normalized.size() - 1] == ' ') {
        normalized.resize(normalized.size() - 1);
    }

    return normalized;
}

std::string UsunSlowo(std::string str, int n)
{
    std::string without = "";
    int m = 0;

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ' && (i == 0 || str[i-1] == ' ' || str[i-1] == '.' || str[i-1] == ',')) {
            m++;
        }
        if (m != n || str[i] == ' ' || str[i] == '.' || str[i] == ',') {
            without += str[i];
        }
    }

    return without;
}

std::string NajwiekszeSlowo(std::string str)
{
    std::string word = "";
    std::string word_temp = "";
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            word_temp += str[i];
        }
        else {
            if (word_temp > word) {
                word = word_temp;
            }
            word_temp = "";
        }

        // Check also the last word
        if (i == str.size() - 1 && word_temp > word) {
            word = word_temp;
        }
    }
    return word;
}

// vim: fen
