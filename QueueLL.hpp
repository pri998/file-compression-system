#ifndef QUEUE_LL_HPP
#define QUEUE_LL_HPP

#include "SinglyLinkedList.hpp" // Assuming SinglyLinkedList is defined in SinglyLinkedList.hpp

template <typename T>
class QueueLL {
private:
    SinglyLinkedList<T> list;

public:
    QueueLL() = default;

    bool isEmpty() const {
        return list.isEmpty();
    }

    int size() const {
        return list.size();
    }

    void offer(const T& elem) {
        list.addLast(elem);
    }

    T poll() {
        return list.removeFirst();
    }

    T peek() const {
        return list.getHeadData();
    }
};

#endif // QUEUE_LL_HPP
