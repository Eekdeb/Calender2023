#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <memory>
#include <type_traits>

/*
Testign how Object Oriented programing works in c++
Making a abstract class with two child classes. These
are then put in a vector together.
*/
class sport{
    protected:
        int state = 6;
    public:
        virtual void printSport() =0; 
};

class Climbing: public sport{
    
    public:
        int a = state;
        void printSport(){
            std::cout << "climbing" << std::endl;
        }
};

class Sprint: public sport{
    public:
        void printSport(){
            std::cout << "Sprint" << std::endl;
        }
};

/*unique eller sheard*/
int main(){    
    std::shared_ptr<Climbing> foo1 = std::make_shared<Climbing>();
    std::shared_ptr<Sprint> foo2 = std::make_shared<Sprint>();
    std::vector<std::shared_ptr<sport>> sports;
    sports.push_back(foo1);
    sports.push_back(foo2);
    for (auto s : sports)
    {
        s->printSport();
        if (auto climbingPtr = std::dynamic_pointer_cast<Climbing>(s)) {
            std::cout << "In Climbing a = " << climbingPtr->a << std::endl; // safe to call
        }
    }
    bool a = 0;
    a = a==0?1:0;
    std::cout << a << std::endl;
    a = a==0?1:0;
    std::cout << a << std::endl;
}