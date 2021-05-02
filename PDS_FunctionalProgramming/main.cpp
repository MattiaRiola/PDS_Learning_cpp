#include <iostream>
#include <vector>
/* functional object and function pointers*/

template <typename F>
void some_function(F f){ //f must be callable
    f(); //it can be a functional object or a function pointer
}

template <typename F>
void print_the_returned_value(F f, int a, int b){
    std::cout << f(a,b) << std::endl;
}

int main() {


    void (*myFunc) (void) = [](void){
        std::cout << "Hello I'm myFunc! And it is made with a lambda expression\n";
        };

    
    some_function(myFunc);

    std::vector<int> v;
    std::for_each(v.begin(),v.end(),[](int i){});
    int scale_factor = -10;
    int a = 7;
    int b = 7;
    // I've to write explicitly the return type if it is "ambiguous"
    print_the_returned_value([scale_factor](int x,int y)->double {
        if(x==y)
            return x*scale_factor;
        else
            return (x>y)  ? (double) x/ (double)y : (double) y / (double) x;
    },a,b);
    b=-1234;
    print_the_returned_value([scale_factor](int x,int y)->double {
        if(x==y)
            return scale_factor * x;
        else
            return scale_factor * ((x>y)  ? (double) x/ (double)y : (double) y / (double) x);
    },a,b);


        


    return 0;
}
