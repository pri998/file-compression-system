#include <iostream>
#include <string>
using namespace std;

class CharNode {
public:
    char character;
    string encoding;
    int freq;
    CharNode* next;

    CharNode(char ch, const std::string& code, int frequency)
        : character(ch), encoding(code), freq(frequency), next(nullptr) {}
};

class CharLinkedList {
private:
    CharNode* headNode;
    CharNode* tailNode;
    int listSize;

public:
    // Constructor
    CharLinkedList() : headNode(nullptr), tailNode(nullptr), listSize(0) {}

    // Check if the list is empty
    bool isEmpty() const {
        return headNode == nullptr;
    }

    // Return the size of the list
    int size() const {
        return listSize;
    }

    // Add a new node to the list
    void add(char ch, const std::string& code, int frequency) {
        CharNode* newNode = new CharNode(ch, code, frequency);
        if (isEmpty()) {
            headNode = tailNode = newNode;
        } else {
            tailNode->next = newNode;
            tailNode = newNode;
        }
        ++listSize;
    }

    // Find a node with a specific character
    CharNode* getCharNode(char ch) const {
        if (isEmpty()) return nullptr;
        CharNode* current = headNode;
        while (current != nullptr) {
            if (current->character == ch) return current;
            current = current->next;
        }
        return nullptr;
    }

    // Get the head node of the list
    CharNode* getHead() const {
        return headNode;
    }
};
