/*----------------------------------------------------------
 * Lab #3: Queues
 *
 * Date: 02-Oct-2024
 * Authors:
#           A01751433 Israel Gonzalez Huerta
#           A01751729 Andres Mendez Cortez
 *----------------------------------------------------------*/
#pragma once
#include <iostream>

template <typename T>
class Queue{
    public:
    //complexity O(1)
    Queue(int capacity){
        _capacity=capacity+1;
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
        return _capacity-1;
    }

    //complexity O(1)
    void enqueue(T value){
        // me hacia cosas feas con el mod 
        if((_next+1)%_capacity==_last){
            throw std::overflow_error("Queue Overflow!");
        }
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
        _last=0;
        _next=0;
        _size=0;

    }

    //complexity O(1)
    T peek() const{
        if (is_empty()) {
            throw std::underflow_error("Queue Underflow");
        }
        return _data[_last];
    }

    //complexity O(1)
    bool is_empty() const{
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
