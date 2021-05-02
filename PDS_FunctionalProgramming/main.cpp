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
    int scale_factor = 2;
    int a = 7;
    int b = 7;
    // I've to write explicitly the return type if it is "ambiguous"
    print_the_returned_value([scale_factor](int x,int y)->double {
        //scale_factor++; //compile error: it is not mutable here
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

    // inside the [] of a lambda function I pass parameters outside that function (for example the scale factor)
    // in the previous calls I've passed it by value and it can't be modified

    // if i want modify a private value outside the lambda function I can put in the [] as reference
    print_the_returned_value([&scale_factor](int x,int y)->double {
        //I can change the value here:
        scale_factor=0;
        if(x==y)
            return scale_factor * x;
        else
            return scale_factor * ((x>y)  ? (double) x/ (double)y : (double) y / (double) x);
    },a,b);
    //now scale factor is = 0!!!
    print_the_returned_value([scale_factor](int x,int y)->double {

        if(x==y)
            return scale_factor * x;
        else
            return scale_factor * ((x>y)  ? (double) x/ (double)y : (double) y / (double) x);
    },a,b);


        


    return 0;
}
