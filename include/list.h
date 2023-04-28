#pragma once
#include <iostream>


template<typename T>
struct Node {
    T data;
    Node* next;
    Node* previous;
};

template<typename T>
class List {
    std::size_t size;
    Node<T>* head;
    Node<T>* tail;
public:
    
    List()
    : size(0), head(nullptr), tail(nullptr){}

    Node<T>* getHead()
    {
        return head;
    }

    Node<T>* getTail()
    {
        return tail;
    }

    void append(T data)
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = data;
        newNode->next = nullptr;

        if (tail != nullptr)
        {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        } else {
            head = newNode;
            tail = newNode;
            newNode->previous = nullptr;
        }

        size++;
    }

    Node<T>* getNode(std::size_t index)
    {
        Node<T>* tmp = head;
        for (std::size_t i = 0; i < index; i++)
        {
            tmp = tmp->next;
        }
        return tmp;
    }

    T& get(std::size_t index)
    {
        return getNode(index)->data;
    }

    void removeNode(Node<T>* node)
    {
        if (node == nullptr) return;
        if (size == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else if (node == head)
        {
            head = head->next;
            head->previous = nullptr;
        } else if (node == tail) {
            tail = tail->previous;
            tail->next = nullptr;
        } else {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }
        delete node;
        size--;
    }

    void insertAfter(Node<T>* node, T data)
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = data;
        newNode->next = node->next;
        newNode->previous = node;
        if (newNode->next != nullptr)
        {
            newNode->next->previous = newNode;
        }
        node->next = newNode;
        size++;
    }

    void remove(std::size_t index)
    {
        Node<T>* node = getNode(index);
        removeNode(node);
    }

    std::size_t getSize()
    {
        return size;
    }

    ~List()
    {
        Node<T>* tmp;

        while (head != nullptr)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};