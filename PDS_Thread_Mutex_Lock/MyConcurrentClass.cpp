//
// Created by Mattia Riola on 03/07/21.
//

#include "MyConcurrentClass.h"




MyConcurrentClass::MyConcurrentClass(){
    stop = false;
    cnt=0;
    t = std::thread([this]() {
        while(!this->stop) {
            //TODO: do it with condition variable, to mute and unmute the class correctly
            std::cout << "Hello world!" << std::endl;
            this->cnt++;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        return this->cnt;
    });
}

MyConcurrentClass::~MyConcurrentClass(){
    t.join();
    std::cout <<"The class said hello "<< this->cnt << " times\n";
}

void MyConcurrentClass::mute() {
    stop=1;
    return;
}

void MyConcurrentClass::unmute() {
    stop = 0;
    std::cerr << "Unmute doesn't work, it needs a condition variable!" << std::endl;
    return;
}