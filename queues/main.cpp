#include <iostream>
#include "queue.h"
int main(){
    Queue<int> a(2);
    std::cout<<a.size()<<"\n";
    std::cout<<a.capacity()<<"\n";
    a.enqueue(3);
    std::cout<<a.size()<<"\n";
    a.enqueue(4);
    std::cout<<a.size()<<"\n";
    std::cout<<a.peek()<<"\n";



    std::cout<<"bool a done"<<"\n";
    return 0;
}