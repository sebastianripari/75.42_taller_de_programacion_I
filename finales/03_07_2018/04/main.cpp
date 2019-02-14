/*
Indicar la salida del siguiente programa:

class Base {
public:
    static void f1() { cout << "Base.f1" << endl; }
    virtual void f2() { cout << "Base.f2" << endl; f1(); }
    virtual void f3() { cout << "Base.f3" << endl; f2(); f1(); }
};

class Derivada : Base {
    static void f1() { cout << "Derivada.f1" << endl; }
            void f2() { cout << "Derivada.f2" << endl; f1(); }
            void f3() { cout << "Derivada.f3" << endl; f2(); f1(); }

};

void main() {
   Derivada D;
   Base*  pB = &D;
    pD->f1();
    pD->f2();
    pB->f1();
    pB->f2();
}
*/

#include <iostream>

class Base {
public:
    static void f1() {
        std::cout << "Base.f1" << std::endl;
    }

    virtual void f2() {
        std::cout << "Base.f2" << std::endl;
        f1();
    }

    virtual void f3() {
        std::cout << "Base.f3" << std::endl;
        f2();
        f1();
    }

};

class Derivada : public Base {
public:
    static void f1() {
        std::cout << "Derivada.f1" << std::endl;
    }

    void f2() {
        std::cout << "Derivada.f2" << std::endl;
        f1();
    }

    void f3() {
        std::cout << "Derivada.f3" << std::endl;
        f2();
        f1();
    }
};

int main() {
    Derivada D;
   
    Derivada* pD = &D;
    ///////////////////////////////////////////////
    std::cout << std::endl;
    /*
    Se llama a f1 de la clase Derivada.
    */
    pD->f1();
    // Derivada.f1     
    /////////////////////////////////////////////////    

    ////////////////////////////////////////////////
    /*
    Se llama a f2 de la clase Derivada.
    Que a su ves llama a f1 de la clase Derivada.
    */
    std::cout << std::endl;
    pD->f2();
    // Derivada.f2 
    // Derivada.f1   
    /////////////////////////////////////////////// 

    Base* pB = &D;
    ////////////////////////////////////////////////
    /*
    pB apunta a es un puntero a una Base, y como
    esta llamando a una funcion estatica se llama a 
    f1 de la clase Base.
    */
    std::cout << std::endl;
    pB->f1();
    // Base.f1
    ////////////////////////////////////////////////

    ////////////////////////////////////////////////
    /*
    pB apunta a una derivada, por lo tanto.
    Se llama a f2 de la clase Derivada.
    Que a su ves llama a f1 de la clase Derivada.
    */
    std::cout << std::endl;
    pB->f2();
    // Derivada.f2
    // Derivada.f1
    /////////////////////////////////////////////////

    /*
    Concluciones:
    1) No importa de que tipo sea el puntero, si el metodo no es estatico,
    y el padre lo tiene virtual, entonces siempre llama a el metodo de la 
    clase que es realmente. Esto se deduce de cuando se llama a f2 con pB y pD.

    2) Si el metodo es estatico entonces no importa la herencia ni de que tipo
    sea la instancia, siempre se llama a el metodo de clase, del tipo que sea 
    ese puntero.
    */

    return 0;
}