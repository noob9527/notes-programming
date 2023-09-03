# cpp

> Note: Currently，I know nothing about the build system in C++. To run tests, open the directory with CLion. Clion will get everything setup for you. 

### WTF moments!
#### syntax of pure virtual function
```c++
class Sample {
    virtual void fun() = 0;
};
```

#### increments and decrements operator overloading(postfix form vs prefix form)
Compare to kotlin's inc() and dec() operator, C++'s increase mutates object inherently. (whereas kotlin mutates the reference which refer to the object)  
the signature to overload postfix form of increase operator looks ridiculous.
```c++
class Operand {
    public:
    int value;
    Operand(int value) : value(value) {};

    /**
     * overload prefix form of increase operator
     * e.g. ++operand
     * here we return `Operand &`, align to the c++'s custom
     * @return returned value should be a reference to *this
     */
    Operand &operator++() {
        value++;
        return *this;
    }

    /**
     * overload postfix form of increase operator
     * e.g. operand++
     *
     * The operator symbol for both prefix(++i) and postfix(i++) are the same.
     * Hence, we need two different function definitions to distinguish between them.
     * This is achieved by passing a dummy int parameter in the postfix version. (ridiculous)
     * @param k
     * @return returned value should be a copy of the object before increment
     */
    Operand operator++(int k) {
        // call default copy constructor
        Operand tmp = (*this);
        value++;
        return tmp;
    }
};

int main() {
    Operand a(0);
    Operand &res1 = ++a;
    // somehow I got to add a 'const' here to make the code compile.
    const Operand &res2 = a++;
}
```

#### incredible "const_cast"
```c++
const int value = 10;
int *ptr = (int *) &value;
*ptr = 20;

cout << "value: " << value << endl;         // => 10
cout << "&value: " << &value << endl;       // => 0x7ffe18f5d754
cout << "ptr: " << ptr << endl;             // => 0x7ffe18f5d754
cout << "*ptr: " << *ptr << endl;           // => 20
```
