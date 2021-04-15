#include <iostream>
template <typename T>
const T& max(const T& t1, const T& t2);
class Person{
public:
    int id;
    static int counter;
    int getId(){ return id;}
    Person(){ counter++;id = counter;}
private:
    std::string name;
    std::string surname;
};
template <typename T>
class Accum{
    T total;
public:
    Accum(T start): total(start){}
    T operator+=(const T& t){
        return total = total+t;
    }
    T value(){return total;}
};
template class Accum<Person>{
    int total;
public:
    Accum(int start = 0): total(start){};
    int operator+=(const Person &){return ++total;}
    int value(){return total;}

};

int Person::counter;
int main() {
    std::cout << "Hello, World!" << std::endl;
    int maxNumber = max(10,5);
    std::cout << "This is the max between 10 and 5 : " << maxNumber << std::endl;
    Person p1 = Person();
    Person* p2 = new Person();
    std::cout << "id of p1 and p2" << std::endl;

    delete p2;
    return 0;
}

template <typename T>
const T& max(const T& t1, const T& t2){
    return (t1<t2 ? t2 : t1);
}



