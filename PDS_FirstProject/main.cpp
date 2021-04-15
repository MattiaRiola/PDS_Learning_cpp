#include "ExternalClass.h"



/* Classi */

class Counter {
private:
    int id;
public:
    static int count;
    Counter(){ count++; id = count;}
    int getCount(){return count;}
    int getId(){return id;}
};
int Counter::count;

class Prova{
    int val;
    char *str;
public:
    //Costruttori

    Prova(): val(0), str("ciao") {
        std::cout<<"sto inizializzando un oggetto di tipo Prova all'indirizzo: "<<this<<std::endl;
    }
    explicit Prova(int n): val(n), str(""){
        std::cout<<"Prova("<<n<<") "<<this<<std::endl;
    }
    //Distruttori
    ~Prova() {
        std::cout << "~Prova() @" << this << std::endl;
    }
    //Altre funzioni
    int getVal() { return val; }
};

class no_copy {
    int k;
    void* ptr;
public:
    no_copy(int k, void* ptr) : k(k), ptr(ptr){}
    int get_k() { return k; }
    void* get_ptr() { return ptr; }
private:
    no_copy(const no_copy& other) = delete;
};


/*  Variabili globali */
Prova p;


/* Funzioni globali */
//void f_nocopy (char* name,const no_copy& n) { //Con const posso chiamare dei metodi che sono solo const
void f_nocopy (char* name, no_copy& n) {
    std::cout<<name<<" "<<n.get_k()<<", "<<n.get_ptr()<<std::endl;
}
void f() {
//    Prova p(4);
    Prova p{4};
}

/* MAIN */
int main() {
    /* Test con classe Prova */
    std::cout << "Hello, World!" << std::endl;
    Prova p; //inizializza nello stack
    f(); //l'indirizzo è un po' più in basso dello stack
    Prova(4);
    std::cout<< p.getVal()<<std::endl;
    //con i :: posso accedere alla variabile globale
    std::cout<< ::p.getVal()<<std::endl;

    /* Test con no_copy per non permettere la copiatura della classe */
    no_copy n1(10,(void*) 128);
    //non posso copiare n1 perché ho inserito la funzione per non renderla copiabile
    //no_copy n2(n1);

    std::cout<<"n1: "<<n1.get_k()<<", "<<n1.get_ptr()<<std::endl;
   //posso comunque inviare una copia ad una funzione per reference
   f_nocopy("n1",n1);

//   ExternalClass t1("nome1"),t2("nome2"),t3("nome3");
//    t1.printInfo();
//    t2.printInfo();
//    t3.printInfo();
    Counter c1;
    int tmp = c1.getCount();
    std::cout << "This is the counter should be 0:  "<<c1.getCount()<< std::endl;

   return 0;
}

