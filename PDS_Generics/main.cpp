#include <iostream>

template <typename T>
const T& max(const T& t1, const T& t2);
class Person{
public:
    std::string name;
    std::string surname;
    int age;
    Person(std::string name, std::string surname, int age) :
        name(name), surname(surname), age(age) { };

    Person& operator+=(const Person& other){
        this->age+=other.age;
        return *this;
    }

};
template <typename T>
class Accum{
    T total;
public:
    Accum(T start = 0): total(start){}
    T operator+=(const T& t){
        return total = total+t;
    }
    T value(){return total;}
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    int maxNumber = max(10,5);
//    int maxNumber = max(2,3.14); // compile error because the types are different
    std::cout << "This is the max between 10 and 5 : " << maxNumber << std::endl;
    float maxFloat = max<float>(2,3.14);
    std::cout << "This is the max between 2 and 3.14 : " << maxFloat << std::endl;

    Accum<int> a1(0);
    for(int i = 0; i<10; i++) a1+=i;
    std::cout << "Accumulated value is : " << a1.value() << std::endl;
    Accum<std::string> a2("");
    std::string s{"*"};
    for(int i = 0; i<10; i++) a2+=s;
    std::cout << "Accumulated value is : " << a2.value() << std::endl;


    Person p1 = Person("Eikichi","Onizuka",22);
    Person* p2 = new Person("Mew","Burzi",7);
    p1+=*p2;
    std::cout << "Eikichi age + Burzi age = " << p1.age << std::endl;
    delete p2;
    return 0;
}

template <typename T>
const T& max(const T& t1, const T& t2){
    return (t1<t2 ? t2 : t1);
}



