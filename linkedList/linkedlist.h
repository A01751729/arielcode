/*----------------------------------------------------------
 * Lab #2: Linked Lists
 *
 * Date: 20-Sep-2024
 * Authors:
#           A01751433 Israel Gonzalez Huerta
#           A01751729 Andres Mendez Cortez
 *----------------------------------------------------------*/

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
    void extend(const LinkedList<T>& other){
        for(int i = 0; i < other.size(); i++){
            insert_back(other.get(i));
        }
    }

    T get(int index) const
    {
        Node* p = _sentinel->next;
        if (index >= size()) {
            throw std::out_of_range(
                "Can't remove from an index greater than the amount of elements in the list");
        }
        if (index < 0) {
            throw std::out_of_range(
                "Can't remove from an index smaller than 0");
        }
        if (index > 0 && index < size()) {
            for(int i = 0; i < index; i++) {
                p = p->next;
            }
            
        }
        return p->value;
    }

    void insert_at(int index,T value)
    {
        if (index > size()) {
            throw std::out_of_range("Can't insert at an index greater than the amount of elements in the list");
        }
        if (index < 0) {
            throw std::out_of_range("Can't insert at an index smaller than the amount of elements in the list");
        }
        Node* p = _sentinel;
        if (index >= 0 && index <= size()) {
            for(int i = 0; i <= index; i++) {
                p = p->next;
            }
            Node* q  = new Node;
            q->value = value;
            p->prev->next = q;
            q->prev = p->prev;
            p->prev = q;
            q->next = p;
            _size++;
        }
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
        if (index >= size()) {
            throw std::out_of_range("Can't remove at an index greater than the amount of elements in the list");
        }
        if (index < 0) {
            throw std::out_of_range("Can't remove at an index smaller than the amount of elements in the list");
        }
        if(index >= 0 && index < this->size()) {
            for(int i = 0; i <= index; i++) {
                p = p->next;
            }
            p->prev->next = p->next;
            p->next->prev = p->prev;
            _size--;
        }
        return p->value;
        delete p;
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
