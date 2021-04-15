#include <iostream>
#include <string>
#include <vector>



std::string give_me_string (int n, char c);
void append_n_char(std::string* str, int n, char c);

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string s1 = give_me_string(10,'b'); //variable passed by value
    std::cout << "This is the string: " << s1 << std::endl;
    std::string s2 = "aaaa";
    append_n_char(&s2,10,'c'); //variable passed by reference
    std::cout << "This is the string2: " << s2 << std::endl;

    return 0;
}


std::string give_me_string(int n, char c){
    std::string s = "";
    for(int i = 0; i<n; i++)
        s=s+c;
    return s;

}

void append_n_char(std::string* str, int n, char c){
    for(int i = 0; i<n; i++)
        *str = *str + c;
    return;
}

