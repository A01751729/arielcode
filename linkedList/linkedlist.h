#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>

template<typename T>
class LinkedList {

public:

    //Complexity: O(1)
    LinkedList()
    {
        _sentinel = new Node;
        _sentinel->next = _sentinel;
        _sentinel->prev = _sentinel;
    };

    //Complexity: O(N)
    LinkedList(std::initializer_list<T> args) : LinkedList()
    {
        for (T arg : args) {
            insert_back(arg);
        }
    }

    LinkedList(const LinkedList& other) = delete;

    LinkedList<T>& operator=(const LinkedList& other) = delete;

    //Complexity: O(N)
    ~LinkedList()
    {
        Node* p = _sentinel->next;
        while (p != _sentinel) {
            Node* q = p;
            p = p->next;
            delete q;
        }
        delete _sentinel;
    };

    bool contains(T value) const
    {
        Node* p = _sentinel->next;
        bool found = false;

        while (p != _sentinel) {
            if (p->value == value) {
                found = true;
            }
            p = p->next;
        }
        return found;
    }

    T get(int index) const
    {
        Node* p = _sentinel;
        if (index >= this->size()) {
            throw std::out_of_range(
                "Can't remove from an index greater than the amount of elements in the list");
        }
        if (index <= 0) {
            throw std::out_of_range(
                "Can't remove from an index smaller or greater than 0");
        }
        if (index > 0 && index < this->size()) {
            for(int i = 0; i < index; i++) {
                p = p->next;
            }
            std::cout << "Valor: " << p->value << "\n";
        }
        return p->value;
    }

    //Complexity: O(1)
    void insert_back(T value)
    {
        Node* p = new Node;
        p->value = value;
        p->next = _sentinel;
        p->prev = _sentinel->prev;
        _sentinel->prev->next = p;
        _sentinel->prev = p;
        _size++;
    }

    //Complexity: O(1)
    void insert_front(T value)
    {
        Node* p  = new Node;
        p->value = value;
        p->next = _sentinel->next;
        p->prev = _sentinel;
        _sentinel->next->prev = p;
        _sentinel->next = p;
        _size++;
    };


    //Complexity: O(1)
    bool is_empty() const
    {
        return not _size;
    }

    T remove_at(int index)
    {
        Node* p = _sentinel;
        if(index >= 0) {
            for(int i = 0; i <= index; i++) {
                p = p->next;
            }
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
        } else {
            for(int i = -1; i >= index; i--) {
                p = p->prev;
            }
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
        }
        return 0;
    }

    //Complexity: O(1)
    T remove_back(){
        if(is_empty()) {
            throw std::length_error(
                "Can't remove from an empty list");
        }
        Node* p = _sentinel->prev;
        T result = p->value;
        _sentinel->prev = p->prev;
        p->prev->next = _sentinel;
        delete p;
        _size--;
        return result;
    }

    T remove_front()
    {
        if(is_empty()) {
            throw std::length_error(
                "Can't remove from an empty list");
        }
        Node* p = _sentinel->next;
        T result = p->value;
        _sentinel->next = p->next;
        p->next->prev = _sentinel;
        delete p;
        _size--;
        return result;
    }

    //Complexity: O(1)
    int size() const
    {
        return _size;
    };

    //Complexity: O(N)
    std::string to_string() const
    {
        std::ostringstream result;
        result << "[";
        bool first_time = true;
        Node* p = _sentinel -> next;
        while (p != _sentinel) {
            if(first_time) {
                first_time = false;
            } else {
                result << ", ";
            }
            result << p->value;
            p = p->next;
        }
        result << "]";
        return result.str();
    };

private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
    };

    Node* _sentinel = nullptr;
    int _size = 0;
};
