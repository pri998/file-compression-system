#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Message.h"
#include "HuffmanTree.h"
#include "CharLinkedList.h"

class HuffmanEncoder {
private:
    std::string text;
    Message msgObject;
    HuffmanTree huffmanTree;
    CharLinkedList charset;
    bool hasBeenCompressed;

public:
    HuffmanEncoder(const std::string& text)
        : msgObject(text), huffmanTree(msgObject), hasBeenCompressed(false) {
        this->text = msgObject.getMessage();
        charset = CharLinkedList();
    }

    HuffmanEncoder(const Message& msg)
        : msgObject(msg), huffmanTree(msgObject), hasBeenCompressed(false) {
        this->text = msgObject.getMessage();
        charset = CharLinkedList();
    }

    void compress() {
        lookUp(huffmanTree.getRoot(), "");
        hasBeenCompressed = true;
    }

    // Recursively building a lookup table from a huffman tree
    // using a linked list with their new sequence of bits.
    void lookUp(Node* node, const std::string& s) {
        if (!node->isLeaf()) {
            lookUp(node->left, s + "0");
            lookUp(node->right, s + "1");
        } else {
            charset.add(node->character, s, node->frequency);
        }
    }

    // Returns the percentage of decrease in the size of the message
    double howMuchCompressed() const {
        if (!hasBeenCompressed)
            throw std::runtime_error("ERROR: Message has not been compressed!");
        return ((msgObject.getSize() - getSizeOfSequence()) /
                static_cast<double>(msgObject.getSize())) * 100;
    }

    CharLinkedList get_charset() const {
        return charset;
    }

    std::vector<std::string> compressedBinaryCode() const {
        if (!hasBeenCompressed)
            throw std::runtime_error("ERROR: Message has not been compressed!");
        std::vector<std::string> d(text.length());
        for (size_t i = 0; i < text.length(); ++i) {
            d[i] = charset.getCharNode(text[i])->bit_size;
        }
        return d;
    }

    void indivSequence() const {
        if (!hasBeenCompressed)
            throw std::runtime_error("ERROR: Message has not been compressed!");
        CharNode* trav = charset.getLink();
        while (trav != nullptr) {
            std::cout << trav->ch << ": " << trav->bit_size << std::endl;
            trav = trav->next;
        }
    }

    int getSizeOfSequence() const {
        if (!hasBeenCompressed)
            throw std::runtime_error("ERROR: Message has not been compressed!");
        int totalSize = 0;
        int bits = 0;
        CharNode* n = charset.getLink();
        while (n != nullptr) {
            totalSize += n->frequency * n->bit_size.length();
            bits += n->bit_size.length();
            n = n->next;
        }
        totalSize += (Message::CHAR_SIZE * charset.size()) + bits;
        return totalSize;
    }
};
