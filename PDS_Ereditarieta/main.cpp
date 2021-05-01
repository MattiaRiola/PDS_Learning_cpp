#include <iostream>
#include "casting.h"
#include "crtp.hpp"

class Base1{
protected:
    int b1;
public:
    virtual int m() { return 1;}
};

class Base2{
protected:
    int b2;
public:
    virtual void implement_me() =0; //this is an abstract method, I've to put the name of the function and '= 0'

    int n() { return 2;}
};
class Der: public Base1, public Base2{
public:
    void implement_me(){}
    int m() {return 11;} //it inherits the virtual keyword
    int n() {return 21;}
};
class Der2: private Base1, public Base2{
public:
    void implement_me(){}

    int m2() {return m();}
    int n() {return 42;}
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    Der* ptr = new Der();
    std::cout<<"if I extend classes with the public keyword I can use their methods outside the class"<<std::endl;
    std::cout<<"if I use the virtual keyword before a method all the child will call the method with the same name of the child\n"
        <<"without the virtual keyword the method that will be called is always the method of the parent of that class that contains the method with that name" << std::endl;
    std::cout<<"ptr:"<<ptr<<" ptr->m(): "<<  ptr->m()
        << " ptr->n(): "<< ptr->n() << std::endl;
    std::cout<<"I can also cast the pointer of the class to other base classes"<<std::endl;
    Base1* ptr1=ptr;
    std::cout<<"ptr1:"<<ptr1<<" ptr1->m(): "<<  ptr1->m() << std::endl;
    Base2* ptr2=ptr;
    std::cout<<"ptr2:"<<ptr<<" ptr2->n(): "<<  ptr2->n() << std::endl;

    std::cout<<"if I extend the classes with private keyword i can't use their methods outside the class"<<std::endl;
    std::cout<<"I can't even cast their parents"<<std::endl;
    Der2 *ptr3 = new Der2();
    std::cout << "ptr3->m2() : " << ptr3->m2() <<"\nptr3->m(); and Base1* ptr4 = ptr3; give a compile error because of the private inheritance"<< std::endl;
    std::cout<<"When the method is not virtual the call depends on how is casted the object"<<std::endl;
    std::cout << "ptr3->n() : " << ptr3->n()  << std::endl; // 42 because Der2 has the method but he doesn't know that it extends Base2
    Base2* ptr5 = ptr3;
    std::cout << "ptr5->n() : " << ptr5->n()  << std::endl; //once casted he uses the method of base2 because he knows that ptr5 points a Base2 object

    Base1* b1 = new Der();
    Base2* b2 = new Der();

    std::cout << "b1->m() : " << b1->m() << std::endl;
    std::cout << "b2->n() : " << b2->n() << std::endl;

    std::cout << "OSS:\nm() is 11 (so the method declared in Der) becuase m() is virtual" << std::endl;
    std::cout << "the compiler knows that b1 is a Der Object because uses a virtual method and a virtual table (V-Table) is made by the compiler to take track of inheritance" << std::endl;

    std::cout << "\n\n/!\\ WARNING: if I've one or more virtual methods, having a virtual destructor is a good practice to avoid issues /!\\ \n\n" << std::endl;
    playingWithCasts();
    crtpExample();
    delete ptr;
    delete ptr3;
    return 0;
}
