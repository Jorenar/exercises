#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class Trie {

    struct Node {
        std::map<std::string, Node> val;
    } data;

    void printNodes(const Node& temp, std::string x = "", std::vector<std::string> endings = {})
    {
        endings.push_back(x);
        if (temp.val.empty()) {
            std::cout << " >";
            printSentence(endings);
            std::cout << std::endl;
        }
        else {
            for (const auto& foo: temp.val) {
                printNodes(foo.second, foo.first, endings);
            }
        }
    }

  public:

    static void printSentence(const std::vector<std::string>& sentence)
    {
        for (const auto& w: sentence) {
            std::cout << w << " ";
        }
    }

    void add(const std::vector<std::string>& sentence)
    {
        std::cout << "Adding : ";
        printSentence(sentence);
        std::cout << "\n";

        Node* temp = &data;
        for (const auto& w: sentence) {
            temp = &(temp->val[w]);
        }
    }


    void printPossibleEndings(const std::vector<std::string>& beginningOfSentece)
    {
        std::cout << "Endings for \"";
        printSentence(beginningOfSentece);
        std::cout << "\" are :\n";

        Node* temp = &data;
        for (const auto& w: beginningOfSentece) {
            if (temp->val.find(w) == temp->val.end()) {
                return;
            }
            temp = &(temp->val[w]);
        }
        printNodes(*temp);
        std::cout << std::endl;
    }

    void load(const std::string& fileName)
    {
        std::ifstream file(fileName);
        if (!file) {
            std::cerr << "Error when openning file " << fileName << std::endl;
            return;
        }
        std::string word;
        std::vector<std::string> sentence;
        while (file >> word) {
            sentence.push_back(word);
            // is it end of the sentence?
            if (word.find_last_of('.') != std::string::npos) {
                add(sentence);
                sentence.clear();
            }
        }
    }

};


int main()
{
    Trie dictionary;
    dictionary.load("sample.txt");

    //dictionary.load("hamletEN.txt");

    std::cout << std::endl;

    dictionary.printPossibleEndings({ "Curiosity" });
    dictionary.printPossibleEndings({ "Curiosity", "killed" });
    dictionary.printPossibleEndings({ "The", "mouse", "was", "killed" });

    /*
       std::cout << "Beginning of sentence (ended with single .): ";
       std::string word;
       std::vector<std::string> sentence;
       while(true){
        std::cin >> word;
        if(word == ".")
            break;
        sentence.push_back(word);
        dictionary.printPossibleEndings(sentence);
       }
     */

    return 0;
}

/* Expected output:
 *
 *   Adding : Curiosity killed the cat.
 *   Adding : Curiosity killed the mouse.
 *   Adding : Curiosity saved the cat.
 *   Adding : Curiosity killed the cat and the mouse.
 *   Adding : The cat was killed by curiosity.
 *   Adding : The mouse was killed by cat.
 *   Adding : The mouse was killed by curiosity.
 *
 *   Endings for "Curiosity " are :
 *    > killed the cat and the mouse.
 *    > killed the cat.
 *    > killed the mouse.
 *    > saved the cat.
 *
 *   Endings for "Curiosity killed " are :
 *    > killed the cat and the mouse.
 *    > killed the cat.
 *    > killed the mouse.
 *
 *   Endings for "The mouse was killed " are :
 *    > by cat.
 *    > by curiosity.
 *
 */
