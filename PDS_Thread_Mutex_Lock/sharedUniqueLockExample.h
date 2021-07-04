//
// Created by Mattia Riola on 04/07/21.
//

#ifndef PDS_THREAD_MUTEX_LOCK_SHAREDUNIQUELOCKEXAMPLE_H
#define PDS_THREAD_MUTEX_LOCK_SHAREDUNIQUELOCKEXAMPLE_H
#include <thread>
#include <mutex>
#include <iostream>
#include <shared_mutex>

void playWithSharedLocks();

class sharedUniqueLockExample {

    std::shared_mutex m;
    int num;

public:
    sharedUniqueLockExample(int n): num(n){
        std::cout << "creating the object for the example" << std::endl;
    }
    void lazyPrintNum();
    void incrNum();

    void setNum(int n);

    int getNum();
    void resetNum();
};


#endif //PDS_THREAD_MUTEX_LOCK_SHAREDUNIQUELOCKEXAMPLE_H
