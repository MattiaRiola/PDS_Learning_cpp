#include <iostream>

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
    int n() { return 2;}
};
class Der: public Base1, public Base2{
public:
    int m() {return 11;}
    int n() {return 21;}
};
class Der2: private Base1, public Base2{
public:
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
    std::cout<<"When the method is not virtual and I call it with a child class..."<<std::endl;

    std::cout << "ptr3->n() : " << ptr3->n()  << std::endl;
    Base2* ptr5 = ptr3;
    std::cout << "ptr5->n() : " << ptr5->n()  << std::endl;


    delete ptr;
    delete ptr3;
    return 0;
}
