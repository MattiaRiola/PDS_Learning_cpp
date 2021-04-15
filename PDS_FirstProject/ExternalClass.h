//
// Created by matti on 29/06/2020.
//

#ifndef PDS_FIRSTPROJECT_EXTERNALCLASS_H
#define PDS_FIRSTPROJECT_EXTERNALCLASS_H
#include <string>
#include <iostream>

class ExternalClass {
private:
    int counter;
    int id;
    std::string name;

public :
    ExternalClass(std::string str) : name(str) { counter++; id = counter;};
    void printInfo();
    ~ExternalClass(){
        counter--;
    }
    int getCounter(){
        return counter;
    }
};


#endif //PDS_FIRSTPROJECT_EXTERNALCLASS_H
