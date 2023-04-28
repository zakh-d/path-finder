#include "priority_queue.h"

PriorityQueue::PriorityQueue(std::size_t size)
: queue(size), size(0){}

int PriorityQueue::parent(int i)
{
    return (i + 1) / 2 - 1;
}

int PriorityQueue::left(int i)
{
    return (i + 1) * 2 - 1;
}

int PriorityQueue::right(int i)
{
    return (i + 1) * 2;
}

void PriorityQueue::push(QueueNode node)
{
    size++;

    int i = size - 1;

    while (i > 0 && queue[parent(i)].distance > node.distance)
    {
        queue[i] = queue[parent(i)];
        i = parent(i);
    }
    queue[i] = node;
}

QueueNode PriorityQueue::pop()
{
    QueueNode min = queue[0];
    queue[0] = queue[size - 1];
    size--;
    heapify(size - 1);
    return min;
}

void PriorityQueue::heapify(int i)
{
    int L = left(i);
    int R = right(i);
    int maxps;

    if (L < size && queue[L].distance < queue[i].distance)
    {
        maxps = L;
    } else {
        maxps = i;
    }

    if (R < size && queue[R].distance < queue[maxps].distance)
    {
        maxps = R;
    }

    if (maxps != i)
    {
        QueueNode tmp = queue[i];
        queue[i] = queue[maxps];
        queue[maxps] = tmp;

        heapify(maxps);
    }
}

std::size_t PriorityQueue::getSize()
{
    return queue.getSize();
}