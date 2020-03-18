#include <iostream> /* File: complex-test.cpp */
using namespace std;

class Complex /* File: complex.h */ {
  private:
    float real; float imag;
  public:
    Complex(float r, float i) { real = r; imag = i; }
    void print() const { cout << "(" << real << " , " << imag << ")" << endl; }
    Complex add1(const Complex& x)  // Return by value
    {
        real += x.real; imag += x.imag;
        return (*this);
    }
    Complex* add2(const Complex& x) // Return by value using pointer
    {
        real += x.real; imag += x.imag;
        return this;
    }
    Complex& add3(const Complex& x) // Return by reference
    {
        real += x.real; imag += x.imag;
        return (*this);
    }
};

void f(const Complex a) { a.print(); } // const Complex a = u
void g(const Complex* a) { a->print(); } // const Complex* a = &u
void h(const Complex& a) { a.print(); } // const Complex& a = u

int main() {
    // Check the parameter passing methods
    Complex u(4, 5); f(u); g(&u); h(u);
    // Check the parameter returning methods
    Complex w(10, 10); cout << endl << endl;
    Complex x(4, 5); (x.add1(w)).print();
    Complex y(4, 5); (y.add2(w))->print();
    Complex z(4, 5); (z.add3(w)).print();
// Complex  temp = *this = x
// Complex* temp =  this = &y
// Complex& temp = *this = z
    cout << endl << endl;          // What is the output now?
    Complex a(4, 5); a.add1(w).add1(w).print();
    Complex b(4, 5); b.add2(w)->add2(w)->print();
    Complex c(4, 5); c.add3(w).add3(w).print();
    return 0;
}
