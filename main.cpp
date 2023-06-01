#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class ObjectIDGenerator {
private:
    int counter;

public:
    ObjectIDGenerator() : counter(0) {}

    int generateID() {
        return ++counter;
    }
};

class SingletonExample {
private:
    static SingletonExample* instance;

    SingletonExample() {}

public:
    static SingletonExample* getInstance() {
        if (instance == nullptr) {
            instance = new SingletonExample();
        }
        return instance;
    }
};

SingletonExample* SingletonExample::instance = nullptr;

class Printable {
public:
    virtual void print() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Printable& obj) {
        obj.print();
        return os;
    }
};

class ConcretePrintable : public Printable {
public:
    void print() const override {
        std::cout << "Printing a concrete object" << std::endl;
    }
};

class Cloneable {
public:
    virtual Cloneable* clone() const = 0;
};

class ConcreteCloneable : public Cloneable {
public:
    ConcreteCloneable* clone() const override {
        return new ConcreteCloneable(*this);
    }
};

class ObjectNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Object not found!";
    }
};

class InvalidIDException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid ID!";
    }
};

void processObject(Printable* obj) {
    ConcretePrintable* concreteObj = dynamic_cast<ConcretePrintable*>(obj);
    if (concreteObj != nullptr) {
    //concreteObj->doSomething();
    }
}

int main() {

    ObjectIDGenerator<int> intIDGenerator;
    int intID = intIDGenerator.generateID();
    std::cout << "Generated ID for int object: " << intID << std::endl;

    SingletonExample* singleton = SingletonExample::getInstance();

    ConcretePrintable concreteObj;
    std::cout << concreteObj << std::endl;

    ConcreteCloneable originalObj;
    ConcreteCloneable* clonedObj = originalObj.clone();

    try {
        throw ObjectNotFoundException();
    }
    catch (const ObjectNotFoundException& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    try {
        throw InvalidIDException();
    }
    catch (const InvalidIDException& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    Printable* printableObj = new ConcretePrintable();
    processObject(printableObj);

    return 0;
}
