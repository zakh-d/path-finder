#pragma once

#include "list.h"
#include "vector.h"

struct QueueNode 
{
    int index;
    int distance;

    QueueNode(){}
    QueueNode(int _index, int _distance)
    : index(_index), distance(_distance){}
    QueueNode(const QueueNode& other) 
    : index(other.index), distance(other.distance){}
};

class PriorityQueue {
    Vector<QueueNode> queue;
    int size;

    int parent(int i);
    int left(int i);
    int right(int i);
    void heapify(int i);
public:
    PriorityQueue(std::size_t size);
    void push(QueueNode node);
    QueueNode pop();
    std::size_t getSize();
};