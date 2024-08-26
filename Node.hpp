#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node {
public:
    Node* left;
    Node* right;
    char character;
    int frequency;

    Node(char character, int frequency, Node* left = nullptr, Node* right = nullptr)
        : character(character), frequency(frequency), left(left), right(right) {
        if (frequency < 0) {
            throw std::invalid_argument("Error: Frequency must be >= 0");
        }
    }

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }

    bool operator<(const Node& that) const {
        if (frequency != that.frequency) {
            return frequency > that.frequency; // Min-heap: lower frequency should be higher priority
        }
        return character > that.character; // Tie-breaker: lower character should be higher priority
    }

    std::string toString() const {
        return std::string(1, character);
    }
};

#endif // NODE_HPP
