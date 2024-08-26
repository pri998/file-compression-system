#include <iostream>
#include <queue>
#include <vector>
#include "Node.h"
#include "Message.h"

class HuffmanTree {
private:
    Node* root;
    Message sequence;

public:
    HuffmanTree(const Message& sequence) : sequence(sequence) {
        if (sequence.isEmpty()) {
            throw std::runtime_error("Error: Sequence of length 0");
        }
        root = buildHuffmanTree();
    }

    Message getMessage() const { return sequence; }

    Node* buildHuffmanTree() {
        auto priorityQueue = populatePQ();

        if (priorityQueue.size() == 1) {
            priorityQueue.push(new Node('\0', 1, nullptr, nullptr));
        }

        while (priorityQueue.size() > 1) {
            Node* left = priorityQueue.top();
            priorityQueue.pop();
            Node* right = priorityQueue.top();
            priorityQueue.pop();
            Node* parent = new Node('\0', left->frequency + right->frequency, left, right);

            priorityQueue.push(parent);
        }

        return priorityQueue.top();
    }

    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> populatePQ() {
        std::priority_queue<Node*, std::vector<Node*>, NodeComparator> pq;
        std::vector<int> freqs = sequence.getFrequencies();
        for (char i = 0; i < freqs.size(); i++) {
            if (freqs[i] > 0) {
                pq.push(new Node(i, freqs[i], nullptr, nullptr));
            }
        }
        return pq;
    }

    // Traversals to traverse through a huffman tree:

    void inOrder() const {
        inOrder(root);
        std::cout << std::endl;
    }

    void preOrder() const {
        preOrder(root);
        std::cout << std::endl;
    }

    void postOrder() const {
        postOrder(root);
        std::cout << std::endl;
    }

    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        std::cout << node->frequency << " ";
        inOrder(node->right);
    }

    void preOrder(Node* node) const {
        if (node == nullptr) return;
        std::cout << node->frequency << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder(Node* node) const {
        if (node != nullptr) {
            postOrder(node->left);
            postOrder(node->right);
            std::cout << node->frequency << " ";
        }
    }

    void levelOrder() const {
        std::queue<Node*> q;
        q.push(root);
        Node* trav;

        while (!q.empty()) {
            trav = q.front();
            q.pop();
            if (trav != nullptr) {
                std::cout << trav->frequency << " ";
                q.push(trav->left);
                q.push(trav->right);
            }
        }
        std::cout << std::endl;
    }

    Node* getRoot() const { return root; }
};

// NodeComparator should be defined to compare nodes in the priority queue.
struct NodeComparator {
    bool operator()(Node* lhs, Node* rhs) const {
        return lhs->frequency > rhs->frequency;
    }
};
