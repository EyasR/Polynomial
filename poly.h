// ----------------------------- poly.cpp/h --------------------------------------
// Eyas Rashid Assignment 1, CSS 343 B, Spring 2019
// Created on: 04/04/2019
// Last Modified on: 09/04/2019
// -----------------------------------------------------------------------------
// Purpose: Creates an abstract data type (ADT) for a polynomial and implements
// the internal representation
// of a polynomial (non-negative exponents) as an array of terms. the array
// element subscript is the exponent and
// the content of the element is the coefficient value. Dynamically allocates
// initial memory for the array using only as many elements as needed. Utilizes
// overloading of operators, accessors, and mutators to manipulate poly objects
// -----------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
// All polynomials have positive exponents.
// ------------------------------------------------------------------------------

#ifndef ASG1_POLY_H
#define ASG1_POLY_H


#include <iostream>
using namespace std;

typedef int Coefficient;
typedef int Exponent;

class Poly {

    friend ostream &operator << (ostream &output, Poly &w);
    friend istream &operator >> (istream &input, Poly &w);

private:
    int* polyArray;
    int arraySize;

public:

    // Constructors
    Poly();
    Poly(Coefficient coeff);
    Poly(Coefficient coeff, Exponent exp);
    Poly(const Poly &a);

    // Destructor
    ~Poly();

    // Member functions
    int getCoeff(Exponent exp) const;
    void setCoeff(Coefficient coeff, Exponent exp);

    // Arithmetic binary operators overload
    Poly operator+( const Poly &rhs) const;
    Poly operator-( const Poly &rhs) const;
    Poly operator*( const Poly &rhs) const;

    // Assignment operators overload
    const Poly &operator=(const Poly &rhs);

    // Logical binary operators overload
    bool operator==( const Poly &rhs ) const;
    bool operator!=( const Poly &rhs ) const;

    // Comparison operators overload
    Poly& operator+=( const Poly &rhs );
    Poly& operator-=( const Poly &rhs );
    Poly& operator*=( const Poly &rhs );

};


#endif //ASG1_POLY_H
