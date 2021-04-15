//
// Created by Mattia Riola on 15/04/21.
//
#include "casting.h"
#include <iostream>
class CBase1{
    int i;
    public:
    virtual void m1(){
        std::cout<<"CBase1->m1()"<<std::endl;
    }
};

class CBase2{
    int j;
public:
    void m1(){
        std::cout<<"CBase2->m1()"<<std::endl;
    }
};

class CDer : public CBase1,public CBase2{
    int k,l;
public:
    void m1(){
        std::cout<<"CDer->m1()"<<std::endl;
    }
};

void playingWithCasts(){
    CDer *d = new CDer();
    CBase1 *b1;
    CBase2 *b2;
    std::cout << "--- static casting ---" << std::endl;
    b1 = static_cast<CBase1 *>(d);
    b2 = static_cast<CBase2 *>(d);
    std::cout << "b1 : " << b1 << std::endl;
    std::cout << "b2 : " << b2 << std::endl;
    std::cout << "OSS:\n 1) b1 != b2\n 2) Il downcast doesn't work " <<std::endl;

    std::cout << "--- dynamic casting ---" << std::endl;
    std::cout << "in order to do the downcast I've to use dynamic cast"<< std::endl;
    b1 = dynamic_cast<CBase1 *>(d);
    b2 = dynamic_cast<CBase2 *>(d);
    std::cout << "b1 : " << b1 << std::endl;
    std::cout << "b2 : " << b2 << std::endl;
    std::cout << "oss: It works as the static_cast but it costs clock cycles in run time" << std::endl;
    CBase1 *b3 = new CBase1();
    CBase2 *b4 = new CBase2();
    CDer *d2;
//    d2 = dynamic_cast<CDer*>(b4); //compile error because CBase2 doesn't have a virtual method  so it doesn't have a V-Table pointer
    d2 = dynamic_cast<CDer *>(b3); //it works because CBase1 has at least 1 virtual method
    std::cout << "d2 : " << d2 << " = NULL" << std::endl;

    std::cout << "OSS: in this way I can check (with an d2==NULL) if the cast is legit or not" << std::endl;

    std::cout << "--- reinterpret_cast ---"<<std::endl;
    std::cout << "it just says to compiler that the variable will be considered as another type without any convertion or pointer modification ( = C like casting)" << std::endl;
    std::cout << "this is useful for low level casts and SO calls"<<std::endl;

    std::cout << "--- const_cast ---"<<std::endl;
    std::cout << "the pointer wont be considered as const anymore" << std::endl;


}
