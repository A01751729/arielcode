#include <iostream>
#include "dinoset.h"

int main()
{
    DinoSet a;
    a.add(DinoId::velociraptor);
    a.add(DinoId::tyrannosaurus);


    DinoSet b;
    b.add(DinoId::triceratops);
    b.add(DinoId::tyrannosaurus);
    b.add(DinoId::pteranodon);
    std::cout << "b = " << b.to_string() << "\n";
    std::cout << "a = " << a.to_string() << "\n";
    std::cout << "a.contains(DinoId::velociraptor) = "
        << a.contains(DinoId::velociraptor) << "\n";
    std::cout << "a.contains(DinoId::tyrannosaurus) = "
        << a.contains(DinoId::tyrannosaurus) << "\n";

    DinoSet c;
    c=a+b;
     std::cout << "c = " << c.to_string() << "\n";


    return 0;
}