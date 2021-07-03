#include <iostream>
#include <fstream>

//required for pipe and fork
#include "unistd.h"
//required for wait
#include <sys/types.h>
#include <sys/wait.h>
#include <chrono>
#include <thread>


void createfile(){
    std::ofstream output_file;
    output_file.open("../input", std::ios::out | std::ios::binary);
    if (!output_file.is_open()){
        std::cout << "File not opened correctly!" << std::endl;
        exit(1);
    }
    for (int i = 0; i < 10; i++){
        output_file.write((char *)& i, sizeof(int));
    }
    output_file.close();
}


void producer(int pipe_fd){
    std::ifstream input_file;
    int val = 0;
    std::cout << "producer start" << std::endl;
    input_file.open("../input");
    if (!input_file.is_open()){
        std::cout << "File not opened correctly!" << std::endl;
        exit(1);
    }

    while(input_file.read((char *)& val, sizeof(int))){
        //without this sleep I don't see that the consumer is waiting on the pipe
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "producer: " << val << std::endl;
        write(pipe_fd, &val, sizeof(val));
    }
    std::cout << "producer end" << std::endl;
    return;
}

void consumer(int pipe_fd){
    int val = 0;
    std::cout << "consumer start" << std::endl;
    while(read(pipe_fd, &val, sizeof(val)) != 0 ){
        std::cout << "consumer: " << val << std::endl;
    }
    std::cout << "consumer end" << std::endl;
    return;
}

int main() {
    int wait_status;

    createfile();   //create a binary file and write some integers into it

    //create two pipes

    //pipefd[0] is the read side of the pipe
    //pipefd[1] is the write side of the pipe

    int parentToChild[2];
    pipe(parentToChild);

    pid_t childPid = fork();

    switch (childPid)
    {
        case -1:
            //something bad happened
            //close pipe and end
            close(parentToChild[0]);
            close(parentToChild[1]);
            break;
        case 0:
            //child
            close(parentToChild[1]);    //close writing end of the pipe
            consumer(parentToChild[0]); //the consumer write to the pipe
            close(parentToChild[0]);    //consumer completed, close read end of the pipe
            break;
        default:
            //parent
            close(parentToChild[0]);    //close reading end of the pipe
            producer(parentToChild[1]); //the producer write to the pipe
            close(parentToChild[1]);    //producer completed, close write end of the pipe
            wait(&wait_status);         //wait for any child (in this case there is only one)
            //waitpid(childPid, &wait_status, 0);   //wait for a specific child
            std::cout << "parent waited for child termination, status: " << wait_status << std::endl;
            break;
    }
    return 0;
}
