#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

template<typename T>
class MinPriorityQueue {
private:
    int size;
    std::vector<T> list;

    void siftDown(int k) {
        while (true) {
            int left = (k * 2) + 1;
            int right = (k * 2) + 2;
            int smallest = left;

            if (right < size) {
                if (isLess(right, left)) {
                    smallest = right;
                }
            }
            if (smallest < size) {
                if (isLess(k, smallest)) {
                    break;
                }
                swap(k, smallest);
                k = smallest;
            } else {
                break;
            }
        }
    }

    void siftUp(int k) {
        int parent_idx = (k - 1) / 2;
        while (k > 0 && isLess(k, parent_idx)) {
            swap(k, parent_idx);
            k = parent_idx;
            parent_idx = (k - 1) / 2;
        }
    }

    bool isLess(int i, int j) const {
        return list[i] <= list[j];
    }

    void swap(int i, int j) {
        std::swap(list[i], list[j]);
    }

public:
    MinPriorityQueue() : size(0) {}

    int len() const { return size; }
    bool isEmpty() const { return size == 0; }

    void add(const T& elem) {
        list.push_back(elem);
        siftUp(size);
        size++;
    }

    T poll() {
        if (size == 0) {
            throw std::runtime_error("Queue is empty");
        }
        return poll(0);
    }

private:
    T poll(int i) {
        if (size == 1) {
            size--;
            T data = list[0];
            list.clear();
            return data;
        }
        size--;
        T data_to_return = list[i];
        swap(i, size);
        list.pop_back();
        siftDown(i);
        return data_to_return;
    }

public:
    std::string toString() const {
        std::stringstream ss;
        ss << "[";
        for (int i = 0; i < size; ++i) {
            ss << list[i];
            if (i < size - 1) {
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }
};
