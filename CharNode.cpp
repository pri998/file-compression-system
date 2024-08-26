#include <string>

using namespace std;

class Node {
public:
    Node* nextNode;
    char character;
    string encoding;
    int freq;

    Node(char ch, const string& code, int frequency)
        : character(ch), encoding(code), freq(frequency), nextNode(nullptr) {}
};
