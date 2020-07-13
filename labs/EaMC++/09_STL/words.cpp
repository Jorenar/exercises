#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>

// I've modified it to be not alphanumeic, but only letters
void toLowerAlpha(std::string& s1)
{
    s1.erase( std::remove_if(s1.begin(), s1.end(), [](unsigned char c) { return !std::isalpha(c); }), s1.end());
    std::transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c) { return std::tolower(c); });
}

int main()
{
    std::string word;
    std::unordered_map<std::string, int> count;
    while (std::cin >> word) {
        toLowerAlpha(word);
        if (word != "") {
            ++count[word];
        }
    }

    std::cout << "Number of distinct words : " << count.size() << std::endl;

    const int topN = 21;

    std::cout << std::endl << "The top " << topN << " most popular words: " << std::endl;

    std::multimap<int, std::string> top;
    std::transform(count.begin(), count.end(), std::inserter(top, top.begin()),
        [](const std::pair<std::string,int>& p) {
            return std::pair<int, std::string>(p.second, p.first);
        });


    if (topN <= top.size()) {
        auto end = top.rbegin();
        std::advance(end, topN);

        for (auto it = top.rbegin(); it != end; ++it) {
            std::cout << it->second << " : " << it->first << std::endl;
        }
    }

    return 0;
}

/* Expected output for ./words < hamletEN.txt
 *
 *    Number of distinct words : 4726
 *
 *    The top 20 most popular words:
 *    the : 1145
 *    and : 967
 *    to : 745
 *    of : 673
 *    i : 569
 *    you : 550
 *    a : 536
 *    my : 514
 *    hamlet : 465
 *    in : 437
 *    it : 417
 *    that : 391
 *    is : 340
 *    not : 315
 *    lord : 311
 *    this : 297
 *    his : 296
 *    but : 271
 *    with : 268
 *    for : 248
 *    your : 242
 *
 */
