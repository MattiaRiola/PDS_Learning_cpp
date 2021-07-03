//
// Created by Mattia Riola on 03/07/21.
//

#ifndef PDS_THREAD_MUTEX_LOCK_MYCONCURRENTCLASS_H
#define PDS_THREAD_MUTEX_LOCK_MYCONCURRENTCLASS_H
#include <thread>
#include <iostream>


class MyConcurrentClass {
    std::thread t;
    bool stop;
    int cnt;
    public:
        MyConcurrentClass();

        void mute();
        void unmute();
        ~MyConcurrentClass();
};


#endif //PDS_THREAD_MUTEX_LOCK_MYCONCURRENTCLASS_H
