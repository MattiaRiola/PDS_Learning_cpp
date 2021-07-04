//
// Created by Mattia Riola on 03/07/21.
//

#include "MyConcurrentClass.h"




MyConcurrentClass::MyConcurrentClass(){
    stop = false;
    loud = true;
    cnt=0;
    t = std::thread([this]() {
        while(!this->stop) {
            //TODO: do it with condition variable, to mute and unmute the class correctly
            if(loud)
                std::cout << "Hello world!" << std::endl;
            this->cnt++;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        return this->cnt;
    });
}

MyConcurrentClass::~MyConcurrentClass(){
    std::cout << "destroying MyConcurrentClass, joining the thread" << std::endl;
    this->stop = true;
    t.join();
    std::cout <<"The class said hello "<< this->cnt << " times\n";
}

void MyConcurrentClass::mute() {
    loud=0;
    return;
}

void MyConcurrentClass::unmute() {
    loud = 1;
    std::cerr << "Unmute doesn't work, it needs a condition variable!" << std::endl;
    return;
}