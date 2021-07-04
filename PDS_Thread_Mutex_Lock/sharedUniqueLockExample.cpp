//
// Created by Mattia Riola on 04/07/21.
//

#include "sharedUniqueLockExample.h"

 void foo(){
    std::cout << "Helo world" << std::endl;
}
void playWithSharedLocks(){
    std::cout << "#### playing with shared locks ####" << std::endl;
    sharedUniqueLockExample A = sharedUniqueLockExample(42);
    std::thread t1([&A](){ A.lazyPrintNum();});
    std::thread t2([&A](){std::cout << "t2 num = "<<A.getNum()<<std::endl;});
    std::thread t3([&A](){A.setNum(100);});
    std::thread t4([&A](){A.lazyPrintNum();});
    std::thread t5([&A](){A.resetNum();});
    std::this_thread::sleep_for(std::chrono::seconds(1)); // wait 1 sec and all except t5 should be completed
    std::thread t6([&A](){A.lazyPrintNum();}); //it should print 0 because it can't acquire the lock because the unique lock is taken by t5
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}

void sharedUniqueLockExample::lazyPrintNum(){
    std::shared_lock l(m);
    std::cout << "before: " << num << std::endl;
    std::cout << "I'm going to sleep... " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "after: " << num << std::endl;
    return;
}

void sharedUniqueLockExample::incrNum(){
    std::unique_lock l(m);
    std::cout << "increment num..." << std::endl;
    num++;
}

void sharedUniqueLockExample::setNum(int n){
    std::unique_lock l(m);
    std::cout << "setting num to " << n << std::endl;
    num=n;
}

int sharedUniqueLockExample::getNum(){
    std::shared_lock l(m);
    std::cout << "getting the num..." << std::endl;
    return num;
}

void sharedUniqueLockExample::resetNum(){
    std::unique_lock l(m);
    std::cout << "I've the (unique) lock and I'm going to sleep for 4 seconds, then I'll reset num" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(4));
    num=0;
}