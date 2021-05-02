#include <iostream>

/* functional object and function pointers*/

template <typename F>
void some_function(F& f){ //f must be callable
    f(); //it can be a functional object or a function pointer
}

int main() {


    void (*myFunc) (void) = [](void){
        std::cout << "Hello I'm myFunc! And it is made with a lambda expression\n";
        };
    some_function(myFunc);

    return 0;
}
