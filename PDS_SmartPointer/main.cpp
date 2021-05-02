#include <iostream>
#include <memory>


class Base;
class Der;
void playWithUniquePtr();
void playWithSharedWeakPtr();
void weakPtrInDepth();


int main() {
    std::cout << "hello world" << std::endl;
    playWithUniquePtr();
    playWithSharedWeakPtr();

    return 0;
}


class Base {
    int value;
public:
    Base(): value(0){std::cout << "default Base's constructor" << std::endl;}
    Base(int v): value(v){std::cout << "Base's constructor value: " << value << std::endl;}
    int getValue() { return value; }
    void setValue(int value) { this->value = value; }
    virtual void virtualPrint(){std::cout << "\nvirtual: hi i'm Base!" << std::endl;}
    void notVirtualPrint(){std::cout << "\nnot virtual: hi i'm Base!" << std::endl;}
    ~Base(){std::cout<<"destructor of Base"<<std::endl; }
};
class Der : public Base{
public:

    virtual void virtualPrint(){std::cout << "\nvirtual: hi I'm Der!" << std::endl;}
    void notVirtualPrint(){std::cout << "\nnot virtual: hi i'm Der!" << std::endl;}

};


void playWithUniquePtr(){
    std::unique_ptr<Base> p1(new Base(42));
    std::unique_ptr<Base> p2;
    std::cout << "p1->getValue() : " << p1->getValue() << "\n";

    std::cout << "\np1 = " << p1 << "\np2 = " << p2 << "\n";
//    b_ptr2 = b_ptr1; //compile error, copy not valid for unique_ptr
    p2 = std::move(p1);
    std::cout << "\n---- after the move ----\n";
    std::cout << "p1 = " << p1 << "\np2 = " << p2 << "\n";
    std::cout << "p2->getValue() : " << p2->getValue() << "\n";
    p2->virtualPrint();

    p1.reset(); // no effect because p1 is nullptr
    p2.reset(); // release the memory of p2 (it will be released anyways at the end of the scope)
    std::cout << "\n---- after the reset ----\n";
    std::cout << "p1 = " << p1 << "\np2 = " << p2 << "\n";

    std::unique_ptr<Base> p3(new Der());
    p3->virtualPrint();
}
void playWithSharedWeakPtr(){
    std::shared_ptr<Base> p1(new Base(9000));
    std::shared_ptr<Base> p2;
    std::shared_ptr<Base> p3;

    std::cout << "shared pointers use a counter to keep track of how many pointers point to that object\n";
    std::cout << "use_count returns the value of that counter";
    std::cout << "p1.use_count(): "<< p1.use_count() << "\n";
    std::cout << "p2=p1;" << "\n";
    p2 = p1;
    std::cout << "p2.use_count(): "<< p2.use_count() << "\n";
    std::cout << "p2.reset();" << "\n";
    p2.reset(); // I can reset a shared ptr and the counter will be decreased
    std::cout << "p2 is nullptr ? " << ( p2 == nullptr ) << "\n";
    std::cout << "p1.use_count(): "<< p1.use_count() << "\n";
    std::cout << "p2.use_count(): "<< p2.use_count() << "\n";

    p3 = std::move(p1); // I can move a shared ptr and p1 will be nullptr
    std::cout << "p1 is nullptr ? " << ( p1 == nullptr ) << "\n";
    std::cout << "p2.use_count(): "<< p3.use_count() << std::endl;

    std::weak_ptr<Base> p4;
    std::cout << "weak_ptr are used as \"watcher\" because they don't touch the counter of the shared ptr"<<"\n";
    p4 = p3;
    std::cout << "p3=p4;\t\t p3.use_count() : "<< p3.use_count()<<"\n";
    p4.reset();
    std::cout << "p4.reset();\t p3.use_count() : " << p3.use_count()<< "\n";
    std::cout << "expired() watch the counter of the smart_ptr of an object" << "\n";
    p4 = p3;
    p2 = p3;
    std::cout << "p3=p4; p2=p3;\nis p4 expired ? "<< p4.expired() << std::endl;
    p3.reset();
    std::cout << "p3.reset(); is p4 expired ? " << p4.expired() << std::endl;
    p4.reset();
    std::cout << "p4.reset(); is p4 expired ? " << p4.expired() << std::endl;

    std::cout << "--- casting shared pointer ---" << std::endl;

    std::shared_ptr<Base> base_ptr = std::make_shared<Der>(); //casting from Der to Base
    std::cout << "base_ptr:" << std::endl;
    base_ptr->virtualPrint();
    base_ptr->notVirtualPrint();
    std::shared_ptr<Der> der_ptr = std::dynamic_pointer_cast<Der>(base_ptr);
    std::cout << "der_ptr:" << std::endl;
    der_ptr->notVirtualPrint();
    der_ptr->virtualPrint();

    std::shared_ptr<Der> der_ptr2 = std::static_pointer_cast<Der>(base_ptr);
    std::cout << "der_ptr2:" << std::endl;
    der_ptr2->notVirtualPrint();
    der_ptr2->virtualPrint();

    std::cout << "I can make a weak_ptr a shared_ptr with the lock() method"<< std::endl;
    weakPtrInDepth();


}

void f(std::weak_ptr<Base> w_p){

    // to check if weak ptr is expired USE lock function and NOT the isExpired
    // because lock is an atomic operation and it works fine with concurrency
    // otherwise I can have this scenario:
    // 1. check if w_p.expired
    // 2. use it
    // between 1 and 2 (in concurrency) the w_p may be expired and I wont be able to use it
    // using w_p.lock() the operation 1 and 2 is atomic in a single one operation and I wont
    // have this kind of behaviours
    if(auto spt = w_p.lock() ) {// useful check before lock a weak ptr
        std::cout << "w_p1.lock(); -> w_p1.use_count() : " << w_p.use_count() << "\n";
        std::cout << "w_p1: " << spt << "\n";
    }
    else 
        std::cout <<" w_p1 is expired" << std::endl;

    return;
}
void weakPtrInDepth(){
    std::weak_ptr<Base> w_p1;
    {
        std::shared_ptr<Base> s_p1 = std::make_shared<Base>(42);
        w_p1 = s_p1;
        std::cout << "s_p1.use_count() : " << s_p1.use_count() << "\n";
        f(w_p1); //w_p1 is not expired yet
    }
    f(w_p1); //w_p1 is expired because s_p1 is out of scope
}