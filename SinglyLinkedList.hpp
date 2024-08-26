#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include <stdexcept>

template <typename T>
class SinglyLinkedList {
private:
    struct LLNode {
        T data;
        LLNode* next;

        LLNode(const T& data, LLNode* next = nullptr)
            : data(data), next(next) {}
    };

    LLNode* head;
    LLNode* tail;
    int size;

public:
    SinglyLinkedList()
        : head(nullptr), tail(nullptr), size(0) {}

    ~SinglyLinkedList() {
        while (!isEmpty()) {
            removeFirst();
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return size;
    }

    T getHeadData() const {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T getTailData() const {
        if (isEmpty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    void addLast(const T& data) {
        LLNode* newest = new LLNode(data);
        if (isEmpty()) {
            head = tail = newest;
        } else {
            tail->next = newest;
            tail = newest;
        }
        ++size;
    }

    T removeLast() {
        if (isEmpty()) {
            throw std::runtime_error("ERROR: List empty");
        }
        if (head == tail) {
            T tail_data = tail->data;
            delete tail;
            head = tail = nullptr;
            --size;
            return tail_data;
        }

        LLNode* tail_prev = head;
        while (tail_prev->next != tail) {
            tail_prev = tail_prev->next;
        }
        T tail_data = tail->data;
        delete tail;
        tail = tail_prev;
        tail->next = nullptr;
        --size;
        return tail_data;
    }

    T removeFirst() {
        if (isEmpty()) {
            throw std::runtime_error("ERROR: List empty");
        }
        LLNode* temp = head;
        T head_data = head->data;
        head = head->next;
        delete temp;
        --size;
        return head_data;
    }
};

#endif // SINGLY_LINKED_LIST_HPP
