#include <iostream>
#include <string>


#define TEST_MAINFILE0 0
#include <iomanip>
#include <fstream>
#define TEST_MAIN0 1
#define TEST_READ_FILE 1
#define TEST_WRITE_FILE 1
#include <vector>
#define TEST_MAIN1 1
#define TEST_MAIN2 1
#define TEST_MAIN3 1
#include <map>
#define TEST_MAIN4 1
#define TEST_MAIN5 1

using namespace std;

template<class T>
void printVector( std::vector<T> vi );

void testMainFile0();
void testWriteFile();
void testReadFile();
void testMain();
void testMain1();
void testMain2();
void testMain3();
void testMain4();
void testMain5();

int main() {
    cout << "Hello, World!" << endl;
    if(TEST_MAINFILE0) {
        testMainFile0();
    }

    //TODO : Gioca con fstream
    if(TEST_WRITE_FILE){
        testWriteFile();
    }

    if(TEST_READ_FILE){
        testReadFile();
    }
    if(TEST_MAIN0){
        testMain();
    }


    if (TEST_MAIN1) {
        testMain1();
    }

    if (TEST_MAIN2) {
        testMain2();
    }

    if (TEST_MAIN3) {
        testMain3();

    }


    if (TEST_MAIN4) {
        testMain4();
    }


    if (TEST_MAIN5) {
        testMain5();
    }

    return 0;
}
template<class T>
void printVector( std::vector<T> vi ){
    cout << "[ ";
//    for(auto v: vi)
//      cout << v << " ";
    for(int i=0; i<vi.size()-1;i++)
        cout << vi[i] << ", ";
    cout << vi[vi.size()-1];
    cout << " ]" << endl;

    return;
}


void testMainFile0(){
    int n = 10;
    //! se non mettessi dec alla fine tradurrei tutti i numeri interi che arrivano al cout come esadecimali
    cout << n << " (0x" << hex << setfill('0') << setw(4) << n << ")" << dec << endl;

    cout << "inserire un numero: ";

    cin >> n;
    if (!cin)
        cout << "errore in lettura" << endl << "ora non dovrei vedere (ma la vedo comunque) la stampa successiva"
             << endl;
    cout << "Bravo! il numero inserito e' : " << n << endl;
}
void testWriteFile(){
    std::ofstream fileOut("provaout.txt",ios_base::out);
    std::cout << fileOut.is_open() << std::endl;
    std::vector<std::string> namesOut;
    namesOut.push_back("Caleb");
    namesOut.push_back("Amy");
    namesOut.push_back("Susan");
    for(std::string name : namesOut){
        fileOut << name << std::endl;
    }
    fileOut.close();

}
void testReadFile(){
    cout << "lettura del file \"prova.txt\"" << endl;
    std::ifstream fileIn("./prova.txt");

    std::string input;
    std::vector<std::string> names;
    cout << "lettura con \"fileIn >> input\" ";
    cout << "- (legge una parola alla volta)" << endl;
    while (fileIn >> input) {
        names.push_back(input);
    }
    for (auto name : names) {
        std::cout << name << std::endl;
    }
    fileIn.close();

    cout << "lettura con \"getline(fileIn,line)\" ";
    cout << "- (legge una linea alla volta)" << endl;
    fileIn = std::ifstream ("prova.txt");
    std::string line;
    std::vector<string> lines;
    while (!fileIn.eof()) {
        getline(fileIn,input);
        lines.push_back(input);
    }
    for(std::string l : lines)
        cout << l << endl;
    fileIn.close();
}
void testMain(){
    cout << "##### Start TEST_MAIN0 #####" << endl;
    cout << "----- Vector and iterator -----" << endl;
    vector<int> vi;
    vi = {1,2,3,4,5};
    cout << "vettore di partenza" << endl;
    printVector(vi);
    cout << "push_back(6)" << endl;
    vi.push_back(6);
    printVector(vi);
    cout << "Size del vettore: " << vi.size() <<endl;
    cout << "Capacity del vettore: " << vi.capacity() <<endl;
    vi.shrink_to_fit();
    cout << "Shrink to fit fatta" << endl;
    cout << "Capacity del vettore: " << vi.capacity() <<endl;
    vi.resize(4);
    cout << "Applico la resize(4)" << endl;
    printVector(vi);
    vector<int>::iterator it = vi.begin();
    cout << "Aggiungo 0 all'inizio e poi aggiungo -1 all'inizio" << endl;
    vi.insert(it,0);
    printVector(vi);
    it = vi.begin();
    vi.insert(it,-1);

    printVector(vi);

    cout << "##### End TEST_MAIN0 #####" << endl;
}

void testMain1(){
    std::cout << "##### Start TEST_MAIN1 #####" << std::endl;
    std::cout << "----- List and iterator -----" << std::endl;

    //TODO: play with list and iterators

    std::cout << "##### End TEST_MAIN1 #####" << std::endl << std::endl;

}
void testMain2(){
    std::cout << "##### Start TEST_MAIN2 #####" << std::endl;
    std::cout << "----- Set and iterator -----" << std::endl;

    //TODO Gioca con Set

    std::cout << "##### End TEST_MAIN2 #####" << std::endl << std::endl;

}

void testMain3(){
    std::cout << "##### Start TEST_MAIN3 #####" << std::endl;
    std::cout << "----- Map and iterator -----" << std::endl;
    std::map<std::string ,int> m1;
    m1.insert({"POST",55});
    m1.insert({"GET",200});
    m1.insert({"POST",40});
    m1.insert({"POST",120});
    m1.insert({"GET",280});
    int i = m1["GET"];
    std::cout << i << std::endl;

    std::cout << "----- map<string,map> and iterators -----" << std::endl;
    std::map<std::string,std::map<std::string,std::string>> outer_map;
    {
        std::map<std::string, std::string> inner_map1;
        inner_map1.insert({"file0", "0000000000000"});
        inner_map1.insert({"file1", "1111111111111"});
        inner_map1.insert({"file2", "2222222222222"});
        outer_map.insert({"user1",inner_map1});
        for(auto i = inner_map1.begin(); i != inner_map1.end(); ++i)
            std::cout << i->first << "\t" << i->second << std::endl;
    }
    std::string user("user1");
    std::map<std::string,std::string> map_tmp = outer_map[user];
    for(auto i = map_tmp.begin(); i != map_tmp.end(); ++i)
        std::cout << i->first << "\t" << i->second << std::endl;

    std::cout << "##### End TEST_MAIN3 #####" << std::endl << std::endl;

}

void testMain4(){
    std::cout << "##### Start TEST_MAIN4 #####" << std::endl;
    std::cout << "----- Miscuglio tra liste mappe vector -----" << std::endl;

    // TODO: Mess with all of the stl

    std::cout << "##### End TEST_MAIN4 #####" << std::endl << std::endl;

}

void testMain5(){
    std::cout << "##### Start TEST_MAIN5 #####" << std::endl;
    std::cout << "----- Stack and deque -----" << std::endl;

    //TODO: Play with stack and dequeue

    std::cout << "##### End TEST_MAIN5 #####" << std::endl << std::endl;


}