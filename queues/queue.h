#pragma once
#include <iostream>

template <typename T>
class Queue{
    public:
    //complexity O(1)
    Queue(int capacity){
        _capacity=capacity;
        _last=0;
        _next=0;
        _size=0;
        _data= new T[_capacity];

    }

    //complexity O(1)
    ~Stack(){
        delete [] _data;
    }

    //complexity O(1)
    int capacity() const{
        return _capacity;
    }

    //complexity O(1)
    bool is_empty(){
        return size()==0;
    }

     //complexity O(1)
    int size() const{
        return _size;

    }

    private:
    T* _data;
    int _capacity;
    int _last;
    int _next;
    int _size;
};
