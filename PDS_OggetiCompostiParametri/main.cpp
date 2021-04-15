#include <iostream>
#include <string>

/**
 * Classe per testare il costruttore di copia
 */
class test {
public:
    int v;
    /**
     * Costruttore (inizializzazione dell'oggetto)
     * @param v
     */
    test(int v) : v(v) {}
    /**
     * costruttore di copia
     * @param other
     */
    test(const test& other): v(other.v) {
        std::cout << "copying " << &other << "into " << this << std::endl;
    }

    test (test&& other): v(other.v){
        std::cout << "moving " << &other << " into " << this << std::endl;
        other.v = 0; 
    }

};


/**
 * Passaggio parametri per valore
 * @param v un intero qualsiasi
 * @return il successivo di v
 */
int foo1(int v){
    std::cout<<"&v: " << &v << " v: " << v << std::endl ;
    v = v+1 ;
    return v ;
}
/**
 *
 * @param v oggetto che vuole incrementare v
 * @return copia dell'oggetto con v incrementato
 */
test foo3_copyClass(test v){
    std::cout<<"&v: " << &v << " v: " << v.v << std::endl ;
    return v.v +=1 ;
}
/**
 *
 * @param v oggetto che vuole incrementare v passato come rvalue
 * @return copia dell'oggetto con v incrementato
 */
test foo3_rvalue(test&& v){
    std::cout<<"&v: " << &v << " v: " << v.v << std::endl ;
    v.v +=1 ;
    return v;
}


/**
 * Passaggio parametri per valore
 * @param v un numero passato come stringa
 * @return ritorna v con un 1 attaccato con formato stringa
 */
std::string foo2(std::string v){
    std::cout<<"&v: " << &v << " v: " << v << std::endl ;
    v = v+std::to_string(1) ;
    return v ;
}

/**
 * Passaggio parametri per referenza
 * @param v un numero passato come referenza di una stringa
 * @return ritorna v con un 1 attaccato con formato stringa
 */
std::string foo2_ref(std::string &v){ //aggiungo solo & a v
    std::cout<<"&v: " << &v << " v: " << v << std::endl ;
    v = v+std::to_string(1) ;
    return v ;
}

/**
 * Passaggio parametri per puntatore
 * @param v un numero passato come referenza di una stringa
 * @return ritorna v con un 1 attaccato con formato stringa
 */
std::string foo2_ptr(std::string* v){ //devo cambiare un po' di cose
    std::cout<<"&v: " << v << " v: " << *v << std::endl ;
    *v = *v+std::to_string(1) ;
    return *v ;
}

/**
 *
 * @param v oggetto che vuole incrementare v passato come rvalue
 * @return copia dell'oggetto con v incrementato
 */
std::string foo2_rvalue(std::string&& v){
    std::cout<<"&v: " << &v << " v: " << v << std::endl ;
    v +=1 ;
    return v;
}

int main() {

    std::cout << "Hello world!!" << std::endl ;

    /* Test di foo1: passaggio interi per valore */
    std::cout << std::endl;
    std::cout << "Test di foo1: Passaggio valore" << std::endl;
    int i = 5;
    std::cout << "&i: " << &i << " i: "<< i << std::endl;
    int j = foo1(i) ;
    std::cout << "&j: " << &j << " j: "<< j << std::endl;



    /* Test di stringhe (foo2): inizializzazione stringhe */
    std::cout << std::endl;
    std::cout << "Test di foo2: Passaggio valore" << std::endl;
    std::string s_i ;
    std::string s_j ;

    /* Test di foo2: passaggio stringa per valore */
    std::cout << std::endl;
    s_i = "5" ;
    std::cout << "&s_i: " << &s_i << " s_i: "<< s_i << std::endl;
    s_j = foo2(s_i);
    std::cout << "&s_i: " << &s_i << " s_i: "<< s_i << std::endl;
    std::cout << "&s_j: " << &s_j << " s_j: "<< s_j << std::endl;


    /* Test di foo2_ref: passaggio stringa per referenza */
    std::cout << std::endl;
    std::cout << "Test di foo2_ref: Passaggio referenza" << std::endl;
    s_i = "5" ;
    std::cout << "&s_i: " << &s_i << " s_i: "<< s_i << std::endl;
    s_j = foo2_ref(s_i);
    //ho passato il parametro per referenza quindi è cambiato anche i
    //mentre j è una copia a se stante
    std::cout << "&s_i: " << &s_i << " s_i: "<< s_i << std::endl;
    std::cout << "&s_j: " << &s_j << " s_j: "<< s_j << std::endl;

    /* Test di foo2_ptr: passaggio stringa per puntatore */
    std::cout << std::endl;
    std::cout << "Test di foo2_ptr: Passaggio puntatore" << std::endl;
    s_i = "5" ;
    std::cout << "&s_i: " << &s_i << " s_i: "<< s_i << std::endl;
    s_j = foo2_ptr(&s_i);
    //ho passato il parametro per referenza quindi è cambiato anche i
    //mentre j è una copia a se stante
    std::cout << "&s_i: " << &s_i << " s_i: "<< s_i << std::endl;
    std::cout << "&s_j: " << &s_j << " s_j: "<< s_j << std::endl;

    /* Test di foo2_rvalue: passaggio stringa per rvalue */
    std::cout << std::endl;
    std::cout << "Test di foo2_rvalue: Passaggio rvalue" << std::endl;
    std::string i_str{"abc"};
    std::cout << "&i_str: " << &i_str << " i_str: "<< i_str << std::endl;
    std::string j_str = foo2_rvalue(std::move(i_str));
    std::cout << "&i_str: " << &i_str << " i_str: "<< i_str << std::endl;
    std::cout << "&j_str: " << &j_str << "j_str: " << j_str << std::endl;


    /* Convenienze del reference */

    /*Se provo a passare un nullptr a foo2_ptr -> errore -> crash*/
//    s_j = foo2_ptr(nullptr);

    /*Mentre con il reference non mi fa proprio compilare perché NON può essere nullptr*/
//    s_j = foo2_ref(nullptr);

    /*Passando per valore concateno la stringa così:*/
//    s_j = foo2(s_i+s_i); // ho errore di compilazione

    /*Usando la reference non mi fa compilare*/
//    s_j = foo2_ref(s_i+s_i); // ho errore di compilazione

    /*Si possono comunque "creare mostri" ad esempio:*/
//    std::string *ptr = nullptr;
//    foo2_ref(*ptr); //diventa lecito e non mi da errori in compilazione
            /*si può fare anche con ritorni di referenze tra funzioni ecc*/


    /* Test di foo con le classi */
    /* inizializzazione oggetti */
    test i_obj{4};

    /* Test di foo3_copyClass: test sulla costruzione di copia */
    std::cout<<std::endl;
    std::cout << "Test di foo3_copyClass: costruttore di copia" << std::endl;
    std::cout<<"&i_obj" << &i_obj << " i: " << i_obj.v << std::endl;
    test j_obj = foo3_copyClass(i_obj);
    std::cout<<"&i_obj" << &i_obj << " i: " << i_obj.v << std::endl;
    std::cout<<"&j_obj" << &j_obj << " j: " << j_obj.v << std::endl;

    /* Test di foo3_rvalue: Passaggio rvalue */
    std::cout<<std::endl;
    std::cout << "Test di foo3_rvalue: passaggio con rvalue" << std::endl;
    std::cout<<"&i_obj" << &i_obj << " i: " << i_obj.v << std::endl;
    test k_obj = foo3_rvalue(std::move(i_obj)); //con move accetto di svuotare i_obj
    std::cout<<"&i_obj" << &i_obj << " i: " << i_obj.v << std::endl;
    std::cout<<"&k_obj" << &k_obj << " k: " << k_obj.v << std::endl;
    
    return 0;
}
