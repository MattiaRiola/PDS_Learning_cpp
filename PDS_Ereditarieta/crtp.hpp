//
// Created by Mattia Riola on 01/05/21.
//

#ifndef PDS_EREDITARIETA_CRTP_HPP
#define PDS_EREDITARIETA_CRTP_HPP

/*
 * The crtp pattern is useful for duck typing and to
 * separate 2 classes the father of 2 classes
 * I can also impose that the T class that will extend CRTPBase must have
 * some features (such as the << operator etc)
 * Note: CRTPBase<D> != CRTPBase<C>
 */
void crtpExample();
template <typename T>
class CRTPBase{
    int v;
    CRTPBase():v(0){std::cout << "CRTPBase constructor"<<std::endl;}
    friend T;
public:
    int getValue(){
        return v;
    }
    int value() const { return static_cast<const T&>(*this).value(); };
    void setValue(int v) {this->v=v;}
};

class D: public CRTPBase<D> {
// with <D> I make D friend of CRTPBase an in this way D can use the private stuff of CRTPBase
public:
    D(){std::cout << "D constructor"<<std::endl;} //it works because D is friend of CRTPBase, otherwise it couldn't call the constructor of CRTPBase
    int getValue(){
        return v;
    }
    int value(){return 42;}

};



class C: public CRTPBase<C> {
//Same as D
public:
    int value(){return 9000;}
};

void crtpExample(){
    std::cout << "d and c will be instantiate and the constructors will be called (C's constructor doesn't print on std::cout)" << std::endl;
    D d;
    C c;
    std::cout << "note: CRTPBase constructor is called because of the inheritance" << std::endl;
    c.setValue(1);
    std::cout << "c.getValue(): " << c.getValue() << std::endl;
    d.setValue(2);
    std::cout << "d.getValue(): " << d.getValue() << std::endl;

    std::cout   << "Now I use the value function"
                << "d.value(): "
                << d.value()
                << "\nc.value(): "
                << c.value()
                << "\nNote: the child method will be called thanks to crtp paradigm\n"
                << std::endl;

}


#endif //PDS_EREDITARIETA_CRTP_HPP
