#include <iostream>

class ByteNode {
public:
    unsigned char byteValue;
    int occurrence; 
    ByteNode* leftChild; 
    ByteNode* rightChild; 

    ByteNode(unsigned char value, int freq) //constructor
        : byteValue(value), occurrence(freq), leftChild(nullptr), rightChild(nullptr) {}

    // Comparison operator for priority queue or sorting
    bool operator<(const ByteNode& other) const {
        return occurrence < other.occurrence;
    }
};
