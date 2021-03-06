//
// Created by hpf on 18-5-8.
//

#include <cassert>

class Array {
public:
    // 构造函数，传入数组的容量capacity构造Array
    Array(int capacity) {
        data = new int[capacity];
        size = 0;
        this->capacity = capacity;
    }

    // 无参数的构造函数，默认数组的容量capacity=10
    Array() {
        data = new int[10];
        size = 0;
        capacity = 10;
    }

    // 获取数组的容量
    int getCapacity() {
        return capacity;
    }

    // 获取数组中的元素个数
    int getSize() {
        return size;
    }

    // 返回数组是否为空
    bool isEmpty() {
        return size == 0;
    }

    // 在index索引的位置插入一个新元素e
    void add(int index, int e) {
        assert(size < capacity && index >= 0 && index <= size);
        for (int i = size - 1; i >= index; --i) {
            data[i + 1] = data[i];
        }
        data[index] = e;
        size++;
    }

    // 在所有元素前添加一个新元素
    void addFirst(int e) {
        add(0, e);
    }

    // 向所有元素后添加一个新元素
    void addLast(int e) {
        add(size, e);
    }

private:
    int *data;
    int size;
    int capacity;
};

