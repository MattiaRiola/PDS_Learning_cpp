#include <iostream>

enum options_t{ esc = 0 , alias, ds  };

/**
 * Accedere all'originale o accedere all'alias e' la stessa cosa
 */
void testAlias(){
    int num = 10;
    int& alias_di_num = num;
    std::cout << "Questo e' l'alias di num: " << alias_di_num << std::endl;
    alias_di_num++;
    std::cout << "***incremento di alias di num*** "  << std::endl;
    std::cout << "Questo e' num: " << num << std::endl;
    std::cout << "Questo e' l'alias di num: " << alias_di_num << std::endl;

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    bool esc_flag = true;
    int choice = 1;

    while(esc_flag) {
        std::cout << "######## \tMENU\t ############" << std::endl;
        std::cout << "Enter:\t exit:0\t alias:1\t" <<std::endl;
        std::cin >> choice;
        switch(choice){
            case esc:
                esc_flag = false;
                break;
            case alias:
                testAlias();
                break;
            default:
                std::cout << "non valid input" << std::endl;
                break;
        }

    }
    return 0;
}
