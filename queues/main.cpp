#include <iostream>
#include "queue.h"
int main(){
    Queue<bool> a(0);
    std::cout<<a.size()<<"\n";
    std::cout<<a.capacity()<<"\n";
    a.enqueue(true);


    std::cout<<"bool a done"<<"\n";
    return 0;
}