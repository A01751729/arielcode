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

    Queue(const Queue& other) = delete;

    Queue<T>& operator=(const Queue& other) = delete;

    //complexity O(1)
    ~Queue(){
        delete [] _data;
    }

    //complexity O(1)
    int capacity() const{
        return _capacity;
    }

    //complexity O(1)
    void enqueue(T value){
        /* me hace cosas feas con el mod 
        if((_next+1)%_capacity==_last){
            throw std::overflow_error("Queue Overflow!");
        }*/
        _data[_next]=value;
        _next=(_next+1)%_capacity;
        _size++;
    }
    
    //Complexity O(1)
    T dequeue(){
        if (is_empty()) {
            throw std::underflow_error("Queue Underflow");
        }
        T value=_data[_last];
        _last=(_last+1)%_capacity;
        _size--;
        return value;
    }

    //Complexity O(N)
    void clear(){
        while(not is_empty()){
            dequeue();
        }
        _next=0;
        _size=0;

    }

    //complexity O()
    T peek(){
        if (is_empty()) {
            throw std::underflow_error("Queue Underflow");
        }
        T value=_data[_last];
        return value;
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
