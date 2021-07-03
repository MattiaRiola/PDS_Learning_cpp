#include <iostream>
#include <vector> // è una classe template
#include <string>
#include <sstream> //poter creare stringhe con <<
#include <memory> //per gli smartpointer
#include <concepts>
// WARNING: Templated class and functions have to be implemented on .hpp file, using .cpp + .h files will give errors


//TODO: Concepts

template <typename T>
class Base {
    Base(){
        std::cout<<"constructor "<<typeid(T).name()<<" @ "<<this<<"\n";
    }
    friend T;
public:
    ~Base(){
        std::cout<<"destructor "<<typeid(T).name()<<" @ "<<this<<"\n";
    }
    std::string to_string() const { //non sto dicendo che è virtual
        return static_cast<const T&>(*this).to_string(); //lo sto dicendo qui invocando to_string di this
    }
};

class Persona: public Base<Persona>{
    std::string nome;
    std::string cognome;
public:
    /**
     * Costruttore di Persona
     * @param n nome
     * @param c cognome
     */
    Persona(std::string n, std::string c):
        nome(n),
        cognome(c){}
    /**
     * Conversione della persona in una stringa
     * @return
     */
    std::string to_string() const{
        return nome+" "+cognome;
    }
};


class Buffer: public Base<Buffer>{
public:
    std::string to_string() const{
            std::ostringstream oss;
            oss<<"Buffer @"<< this;
            return oss.str();
        }
};

template <typename T>
void print_info(const Base<T>& base){  //devo passare per reference
    std::cout<<base.to_string()<<"\n";
}

std::unique_ptr<Persona> create_persona_uniq(std::string n, std::string c){
    return std::unique_ptr<Persona>(new Persona(n,c));
}

std::shared_ptr<Persona> create_persona_shared(std::string n, std::string c){
//    return std::shared_ptr<Persona>(new Persona(n,c));
    return std::make_shared<Persona>(n,c); // è una funzione che permette di omettere il new
}

/**
 * Non è molto efficace come soluzione,
 * è meglio usare gli smart pointer (guarda main3)
 */
void main2() {
    //usare i puntatori normali
    Persona* p1 = new Persona("Mario","Rossi");
    Persona* p2 = p1;
    print_info(*p1);
    delete p1; //mi devo ricordare di fare la delete
//    print_info(*p2); //!!! attenzione qui sto stampando delle cose non mie! perché p1 è già stato deallocato


    /* usando gli smart pointer*/
    std::unique_ptr<Persona> p3 = create_persona_uniq("Giuseppe","Conti");
    print_info(*p3);
    //non devo chiamare la delete per p3 perché gli smart pointer la fanno per conto loro
//    std::unique_ptr<Persona> p4 = p3; // NON POSSO COPIARLO non mi fa compilare!
    // per muovere (e non copiare) p3 posso fare così:
    std::unique_ptr<Persona> p5 = std::move(p3);
//    print_info(*p3); // null pointer exception! perché p1 è stato distrutto dalla move
    print_info(*p5); //funziona perché da p3 è passato a p5

    std::shared_ptr<Persona> p6 = create_persona_shared("Peppe","Condiviso");
    print_info(*p6);
    std::shared_ptr<Persona> p7 = p6; //senza usare move
    std::cout<<"p6 prima della reset: "<<p6.get()<<"\n";
    p6.reset();
    std::cout<<"p6 dopo la reset: "<<p6.get()<<"\n";
    print_info(*p7);

    return;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::vector<int> v;
    /* aggiunta di elementi */
    for(int i = 0 ; i<1000; i++)
        v.push_back(i);
    std::cout<<"v contiene "<<v.size()<< " elementi\n";

    for (int i = 0; i<2000; i++)
        v.push_back(i);

    std::cout<<"v contiene "<<v.size()<< " elementi\n";
    std::cout<<"v[50] : " <<v[50]<<"\n";


//    for(int i =0; i<v.size();i++)
//        std::cout<<"v["<<i<<"]:"<<v[i]<<"\n";


    /* pulizia degli elementi */
    v.clear();
    std::cout<<"v contiene "<<v.size()<< " elementi\n";

    /* Template classe Persona */
    Persona p1("Mario","Rossi");
//    std::cout<<p1.to_string()<<"\n";
    print_info(p1);
    Buffer b;
//    std::cout<<b.to_string()<<"\n";
    print_info(b);

    /* Gestione dei template con i puntatori tradizionali*/
    main2();

    return 0;
}
