// Section 16
// Interfaces - start

#include <iostream>

class I_Printable { // Apstrktna klasa
    friend std::ostream &operator<<(std::ostream &os, const I_Printable &obj);
public:
    virtual void print(std::ostream &os) const = 0;

};

std::ostream &operator<<(std::ostream &os, const I_Printable &obj) {
    obj.print(os);
    return os;
}


class Account : public I_Printable { 
public:
    virtual void withdraw(double amount) {
        std::cout << "In Account::withdraw" << std::endl;
    }
    virtual void print(std::ostream &os) const override {
        os << "Account Display";
    }
    virtual ~Account() {  }
};

class Checking: public Account  {
    friend std::ostream &operator<<(std::ostream &os, const Checking &acc);
public:
    virtual void withdraw(double amount) {
        std::cout << "In Checking::withdraw" << std::endl;
    }
    virtual void print(std::ostream &os) const override {
        os << "Checking Display";
    }
    virtual ~Checking() {  }
};

class Savings: public Account {
public:
    virtual void withdraw(double amount) {
        std::cout << "In Savings::withdraw" << std::endl;
    }
    virtual void print(std::ostream &os) const override {
        os << "Saving Display";
    }
    virtual ~Savings() {  }
};

class Trust: public Account  {
    friend std::ostream &operator<<(std::ostream &os, const Trust &acc);
public:
    virtual void withdraw(double amount) {
        std::cout << "In Trust::withdraw" << std::endl;
    }
    virtual void print(std::ostream &os) const override {
        os << "Trust Display";
    }
    virtual ~Trust() {  }
};


// Dodat bezveze primer
class Dog: public I_Printable {
    public:
        virtual void print(std::ostream &os) const override {
            os << "Woof woof";
        }
        virtual ~Dog() {  }
};

// Napravi funkciju za main (da ne moras u main: std::cout << *dog << std::endl)
// Pozivas sa: print(*dog);
void print(const I_Printable &obj) {
    std::cout << obj << std::endl; 
}



int main() {

   // bezveze primer
    Dog *dog = new Dog();
    // std::cout << *dog << std::endl; // Rezultat: Woof woof
    print(*dog);                    // Rezultat: Woof woof

    Account *p1 = new Account();
    // std::cout << *p1 << std::endl; // Rezultat: Account Display
    print(*p1);                    // Rezultat: Account Display               

    Account *p2 = new Checking();
    // std::cout << *p2 << std::endl; // Rezultat: Checking Display
    print(*p2);                    // Rezultat: Checking Display




//    Account a;
//    std::cout << a<< std::endl;
//    
//    Checking c;
//    std::cout << c << std::endl;
//
//    Savings s;
//    std::cout << s << std::endl;
//    
//    Trust t;
//    std::cout << t << std::endl;

    delete dog;
    delete p1;  
    delete p2;
    return 0;
}

