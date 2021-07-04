#include <iostream>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <stack>
#include <algorithm>
void playWithCV();
/**
 * insert numbers from 'begin' to 'end' in v with a push_back
 * @param begin from this number
 * @param end to this number
 */
void produce(int begin, int end,int id);
void consume(int numElements, int id);
void smartConsume(int numElements, int id);

std::stack<int> s;
std::mutex m;
std::condition_variable cv;
std::vector<int> resultStorage;
std::vector<int> productionStorage;

int main() {
    std::cout << "Hello, World!" << std::endl;
    playWithCV();



    return 0;
}

void playWithCV() {
    std::cout << "### play with CV ###" << std::endl;
    std::cout << "OSS: if the consumers want more elements than the elements produced by the producers the process wont terminate because the consumers will wait on cv forever\n\n";
    std::thread producer1(produce,0,5,1);
    std::thread producer2(produce,5,10,2);
    std::thread producer3(produce,10,15,3);
    //total number inserted in v = 15
    std::thread consumer1(consume,8,1);
    std::thread consumer2(consume,4,2);
    //total number consumed = 15

    consumer1.join();
    consumer2.join();
    //once the dumb consumers ended I call the smartConsumer
    //the smartConsume will exit if there wont be any elements for 2 seconds in the list
    //so if the producers wont give the elements in this time the program can end without waiting forever
    //thing that it happens with dumb consumer
    std::thread smartConsumer3(smartConsume,10,3);
    producer1.join();
    producer2.join();
    producer3.join();
    smartConsumer3.join();
    std::cout << "final result:\nconsumed:\n\t(not sorted): ";
    std::cout << "[ ";
    for ( int n : resultStorage)
        std::cout << n << " ";

    std::sort(resultStorage.begin(),resultStorage.end(), [](int i, int j){return (i<j);});
    std::cout << "]\n\t(sorted): [ ";
    for ( int n : resultStorage)
        std::cout << n << " ";
    std::cout << "]\n" << std::endl;
    std::cout << "produced:\n\t(not sorted): ";
    std::cout << "[ ";
    for ( int n : productionStorage)
        std::cout << n << " ";

    std::sort(productionStorage.begin(),productionStorage.end(), [](int i, int j){return (i<j);});
    std::cout << "]\n\t(sorted): [ ";
    for ( int n : productionStorage)
        std::cout << n << " ";
    std::cout << "]\n" << std::endl;

    std::cout << "remains: " << productionStorage.size() - resultStorage.size()
        << "elements to be consumed" << std::endl;
}

void produce(int begin, int end, int id){
    for (int i = begin; i < end; i++){
        std::lock_guard lg(m);
        std::cout << "[producer " << id <<"]\t"
            << "produce: " << i << std::endl;
        s.push(i);
        productionStorage.insert(productionStorage.end(),i);
        cv.notify_one();
    }
    std::cout << "[producer " << id <<"]\t"
              << "production finished, producted "
              << end-begin << " elements" << std::endl;

}


void consume(int numElements, int id){
    int i;
    for( i = 0; i<numElements; ++i){
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul,[](){return !s.empty();});
        int data = s.top();
        s.pop();
        resultStorage.push_back(data);
        std::cout << "[consumer " << id
            <<"]\tconsume: " << data << std::endl;

    }
    std::cout << "[consumer " << id
              <<"]\tconsumation finished, consumed "
              << i << " elements" << std::endl;
}

void smartConsume(int numElements, int id){
    int i;
    for(i = 0; i<numElements; ++i){
        std::unique_lock<std::mutex> ul(m);
        if(! cv.wait_for(ul,std::chrono::seconds(2),[](){return !s.empty();}) ){
            std::cout << "I waited for too long, I'm going to exit now" << std::endl;
            break;
        }

        int data = s.top();
        s.pop();
        resultStorage.push_back(data);
        std::cout << "[consumer " << id
                  <<"]\tconsume: " << data << std::endl;

    }
    std::cout << "[consumer " << id
              <<"]\tconsummation finished, consumed "
              << i << " elements" << std::endl;
}