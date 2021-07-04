#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "MyConcurrentClass.h"
#include "sharedUniqueLockExample.h"

void interferenceExample();
void solutionToInterfaceExample();
void parametersIssues();
int differentLocks();
void concurrencyWithClasses();
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "#### example of interference ####" << std::endl;
    interferenceExample();
    std::cout << "#### solution of the interference ####" << std::endl;
    solutionToInterfaceExample();

    parametersIssues();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "#### different types of locks ####" << std::endl;
    std::vector<int> res;
    for(int i = 0; i<10; i++)
        res.push_back(differentLocks());
    std::cout << "results:\n";
    for(int r : res)
        std::cout << " res1: " << r << std::endl;

    concurrencyWithClasses();
    playWithSharedLocks();
    return 0;
}




void interferenceExample(){
    int a;
    int numOfIncrements = 1000000;
    std::cout << "in this example I try to run 2 threads, "
        << "they have no synchronization method and they increments a common variable with 'a++' up to " << numOfIncrements
        << "\n At the end the number wont be: " << numOfIncrements << " + " << numOfIncrements << " = " << numOfIncrements+numOfIncrements
        << "\n because the a++ is not an atomic operation and I've no mutual exclusion\n\n";
    //this is the run function, it is a callable so it can be passed to a thread's constructor
    auto run = [&a,numOfIncrements] () {
        int i = 0;
        while(a>=0 && i < numOfIncrements){
            i++;
            int before = a;
            a++;
            int after = a;
            if(after-before != 1) {
                if(after-before < 0)
                    std::cout << "warning! in this case after-before is negative!\n";
                std::cout << before << " -> " << after << "(" << after - before << ")\n";
            }
        }
        std::cout << "run finished" << std::endl;
    };

    std::thread t1(run);
    std::thread t2(run);
//    std::cout << "after the threads are launched and before the join a = " << a << "\t (this result is unpredictable)\n";
    t1.join();
    t2.join();
    std::cout << "at the end a = " << a << std::endl;

};

void solutionToInterfaceExample(){
    int a;
    int numOfIncrements = 1000000;
    std::mutex m;
    std::cout << "To solve the problem mutex are used to guarantee the mutual exclusion\n";
    //this is the run function, it is a callable so it can be passed to a thread's constructor
    auto run = [&a,numOfIncrements,&m] () {
        int i = 0;
        while(a>=0 && i < numOfIncrements){
            i++;
            std::lock_guard<std::mutex> l(m);
            int before = a;
            a++;
            int after = a;
            if(after-before != 1) {
                if(after-before < 0)
                    std::cout << "warning! in this case after-before is negative!\n";
                std::cout << before << " -> " << after << "(" << after - before << ")\n";
            }
        }
        std::cout << "run finished" << std::endl;
    };

    std::thread t1(run);
    std::thread t2(run);
//    std::cout << "after the threads are launched and before the join a = " << a << "\t (this result is unpredictable)\n";
    t1.join();
    t2.join();
    std::cout << "at the end a = " << a << std::endl;


}

void parametersIssues(){
    char buffer[1024] = "This is my buffer";
    auto f = [](std::string const & s, int numSeconds) {
        std::this_thread::sleep_for(std::chrono::seconds(numSeconds));
        std::cout << "this is the string: " <<s << std::endl;
    };
    std::cout << "start the thread with 'hello' "<< std::endl;
    std::thread t1(f,"hello",1);
    t1.detach();
    //I'm not sure that my buffer is sill "alive" after the detach and this is an ERROR
//    std::cout << "start the thread with (buffer) "<< std::endl;
//    std::thread t2(f,buffer,3);
//    t2.detach();
    std::cout << "start the thread with std::string(buffer) "<< std::endl;
    std::thread t3(f,std::string(buffer),1);
    t3.detach();
    std::this_thread::sleep_for(std::chrono::seconds(2));

}


int differentLocks(){
    std::mutex m1; //related to num
    int num = 0;
    std::mutex m2; //related to valueToSum
    int valueToSum = 1;
    std::mutex m3;
    bool finished = false;
    //summer will add valueToSum to num n times
    auto summer = [&m1,&m2,&num,&valueToSum] (int n) {
        std::cout<< "[thread: " << std::this_thread::get_id() << "]\t start:\tn=" << n << std::endl;
        for(int j = 0; j<n;j++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%100));
            std::scoped_lock l(m1,m2);
            std::cout << "[thread: "<< std::this_thread::get_id() << "]\n\tsum: (num=) " << num << " + (valueToSum=) " << valueToSum << "\n";
            num=num+valueToSum;

        }
    };
    //this will increment the valueToSum
    auto sumIncrementer = [&m2,&valueToSum](){
        std::lock_guard<std::mutex> l(m2);
        valueToSum++;
        std::cout << "now the valueToSum is : " << valueToSum << "\n";

    };
    //this will just print the num
    auto printerWithoutCV = [&m1,&m2,&m3,&num,&valueToSum,&finished] (){
        m3.lock();
        while(!finished) {
            m3.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%500));
            std::scoped_lock<std::mutex, std::mutex> sl(m1, m2);
            std::cout << "snapshot:\t\tnum = " << num << "\t";
            std::cout << "valueToSum = " << valueToSum << "\t";
            m3.lock();
        }
        m3.unlock();
    };
    std::thread t2(summer,6);
    std::thread t1(summer,3);

    std::thread p1(printerWithoutCV);
    t1.join();
    std::thread s1(sumIncrementer);

    s1.join();
    t2.join();
    m3.lock();
    finished=true;
    m3.unlock();
    p1.join();

    std::cout << "final value: num = " << num << std::endl;
    return num;
}

void concurrencyWithClasses(){
    MyConcurrentClass myObject = MyConcurrentClass();
    std::string input = "";
    std::cout << "enter s to end the program, m to mute and u to unmute" << std::endl;
    while(input.compare("s") != 0) {
        std::getline(std::cin, input);
        if(input.compare("m")==0) {
            myObject.mute();
        }
        if(input.compare("u")==0) {
            myObject.unmute();
        }


    }
    std::cout << "escaping the loop" << std::endl;
}