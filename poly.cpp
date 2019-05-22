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

#include "poly.h"

using namespace std;
//-------------------------------------------
//-------------Constructors------------------
//-------------------------------------------

// ------------Poly--------------------------
//Description: Constructor with no parameters
// initializes as 0x^0
//-------------------------------------------
Poly::Poly() {
    this->arraySize = 1;
    polyArray = new int[this->arraySize];
    polyArray[0] = 0;
} // end of poly

// ------------Poly---------------------------
// Description: Constructor with one parameter
// initializes at (coeff value)x^0
//--------------------------------------------
Poly::Poly(Coefficient coeff) {
    this->arraySize = 1;
    polyArray = new int[this->arraySize];
    polyArray[0] = coeff;
} // end of poly

// ------------Poly-----------------------------------------------
// Description: Constructor with two parameters
// initializes at (coeff value)x^(exp), sets array size as exp + 1
// and adds coefficient in the largest array index
//----------------------------------------------------------------
Poly::Poly(Coefficient coeff, Exponent exp) {
    // if exponent is negative set coeff = 0 and exp = 0
    if (exp < 0) {
        this->arraySize = 1;
        polyArray = new int[this->arraySize];
        polyArray[0] = 0;
    } else {
        this->arraySize = exp + 1;
        polyArray = new int[this->arraySize];

        for (int i = 0; i < this->arraySize; i++) {
            polyArray[i] = 0;
        }
    }
    polyArray[exp] = coeff;
} // end of poly

// ------------Poly---------------------------
// Description: Constructor, creates deep copy
// of polynomial array
//--------------------------------------------
Poly::Poly(const Poly &a) {
    this->arraySize = a.arraySize;
    this->polyArray = new int[this->arraySize];

    for (int i = 0; i < this->arraySize; i++) {
        this->polyArray[i] = a.polyArray[i];
    }
} // end of poly

// ------------Poly--------------------------
// Description: Destructor, deletes array
// sets pointer to null
//-------------------------------------------
Poly::~Poly() {
    delete[] polyArray;
    polyArray = NULL;
} // end of ~poly

//-----------------------------------------------------
//-------------Accessors-------------------------------
//-----------------------------------------------------

// ------------output operator overload----------------
// Description: overloads output operator to return
// of poly objects
//-----------------------------------------------------
ostream &operator<<(ostream &output, Poly &w) {
    bool emptyPolyArray = true;

    for (int i = w.arraySize - 1; i >= 0; i--) {
        if (w.polyArray[i] != 0) {
            //flags polynomial as filled
            emptyPolyArray = false;
            // adds space between exponential expressions
            output << " ";
            // if coefficient is positive print +, in front of coefficient value
            if (w.polyArray[i] > 0) {
                output << "+";
            }
            // prints coefficient
            output << w.polyArray[i];
            // if exponent > 1, print x^ after coefficient
            if ((i != 0) && (i != 1)) {
                output << "x^" << i;
            }
            // if exponent = 1, print x after coefficient
            if (i == 1) {
                output << "x";
            }
        }
    }
    // if the polynomial array is empty output is 0.
    if (emptyPolyArray) {
        return output << "0";
    } else {
        return output;
    }
} // end of operator<<

//------------getCoeff--------------------------------
// Description: returns the coefficient of an exponent
// from poly object
//-----------------------------------------------------
int Poly::getCoeff(Exponent exp) const {
    // returns coefficient if exponent (array index) is in
    // bounds(non negative, exists in polynomial size).
    if (exp >= 0 && exp < this->arraySize) {
        return polyArray[exp];
    }
    return 0;
} // end of getCoeff

//-----------------------------------------------------
//-------------Mutators--------------------------------
//-----------------------------------------------------

//------------input operator overload----------------
// Description: overloads input operator to return
// of poly objects
//-----------------------------------------------------
istream &operator>>(istream &input, Poly &w) {
    Coefficient coeff = 0;
    Exponent exp = 0;
    w.arraySize = -1;
    bool isEmpty = true;


    while (input >> coeff >> exp) {

        if (coeff == -1 && exp == -1){
            if (isEmpty == true){
                w.setCoeff(0,0);
            }
                break;
        }
        isEmpty = false;
        w.setCoeff(coeff, exp);
    }
    return input;
} // end of operator>>

//------------setCoeff--------------------------------
// Description: sets the coefficient and exponent
// of a poly object
//-----------------------------------------------------
void Poly::setCoeff(Coefficient coeff, Exponent exp) {

    // checks if exponent is positive
    if (exp >= 0) {
        // checks if exponent is in bounds of array
        if (exp < this->arraySize) {
            polyArray[exp] = coeff;    // assigns coefficient to index power
        }
            // mutates polynomial array to incorporate new polynomial value
        else {
            int *tempArray = new int[exp + 1];  // temporary array

            // copies polynomial values from original array to temporary array
            for (int i = 0; i < this->arraySize; i++) {
                tempArray[i] = polyArray[i];

            }

            // assigns 0 to remainder of temporary array indexes
            for (int j = this->arraySize; j < exp + 1; j++) {
                tempArray[j] = 0;
            }

            // assigns coefficient value to concurent exponent index in temporary array
            tempArray[exp] = coeff;

            delete[] polyArray;  // deletes old original array
            polyArray = NULL;    // sets pointer to NULL
            polyArray = tempArray; // sets pointer to temp array
            tempArray = NULL;     //  sets temporary arrays pointer to NULL
            this->arraySize = exp + 1;   // re-asigns size to the size of temporary array
        }
    }
} // end of setCoeff

//-----------------------------------------------------
//-------------Assignment Overloading------------------
//-----------------------------------------------------

//------------operator+--------------------------------
// Description: overloads + operator to utilize
// poly objects
//-----------------------------------------------------
Poly Poly::operator+(const Poly &rhs) const {
    // checks if lhs > rhs
    if (this->arraySize > rhs.arraySize) {
        // new Polynomial to hold sum of lhs & rhs
        Poly polySum(0, this->arraySize);

        // copies poly array into polySum array for evaluation.
        for (int i = 0; i < this->arraySize; i++) {
            polySum.polyArray[i] = this->polyArray[i];
        }
        // adds rhs to polySum array
        for (int i = 0; i < rhs.arraySize; i++) {
            polySum.polyArray[i] += rhs.polyArray[i];
        }
        //returns summation of lhs  & rhs polynomials
        return polySum;
    }
        //rhs > lhs
    else {
        // new Polynomial to hold sum of lhs & rhs
        Poly polySum(0, rhs.arraySize);
        // copies rhs array into polySum array for evaluation.
        for (int i = 0; i < rhs.arraySize; i++) {
            polySum.polyArray[i] = rhs.polyArray[i];
        }
        // adds lhs to polySum array
        for (int i = 0; i < this->arraySize; i++) {
            polySum.polyArray[i] += this->polyArray[i];
        }
        //returns summation of lhs  & rhs polynomials
        return polySum;
    }

} // end of operator+

//------------ operator- ------------------------------
// Description: overloads - operator to utilize
// poly objects
//-----------------------------------------------------
Poly Poly::operator-(const Poly &rhs) const {
    // checks if lhs > rhs
    if (this->arraySize > rhs.arraySize) {

        // create Polynomial object to hold difference of lhs & rhs
        Poly polyDif(0, this->arraySize - 1);

        for (int i = 0; i < this->arraySize; i++) {
            // copies lhs array into polyDif array for evaluation.
            polyDif.polyArray[i] = this->polyArray[i];
        }
        // subtracts rhs to difference array
        for (int i = 0; i < rhs.arraySize; i++) {
            polyDif.polyArray[i] -= rhs.polyArray[i];
        }
        // returns the difference of the polynomials
        return polyDif;
    }
    // rhs > lhs
    else {
        // create Polynomial object to hold difference of lhs & rhs
        Poly polyDif(0, rhs.arraySize - 1);
        // copies lhs array into polyDif array for evaluation.
        for (int i = 0; i < this->arraySize; i++) {
            polyDif.polyArray[i] = this->polyArray[i];
        }
        // subtracts rhs from difference array
        for (int i = 0; i < rhs.arraySize; i++) {
            polyDif.polyArray[i] -= rhs.polyArray[i];
        }
        // returns the difference of the polynomials
        return polyDif;
    }
} // end of operator-

//------------ operator* ------------------------------
// Description: overloads * operator to utilize
// poly objects
//-----------------------------------------------------
Poly Poly::operator*(const Poly &rhs) const {
    //calculates size of the product of lhs * rhs
    int productArraySize = (rhs.arraySize + this->arraySize - 2);

    // new polynomials to hold the product of lhs * rhs
    Poly productArray(0, productArraySize);

    for (int i = 0; i < this->arraySize; i++) {
        // multiplies lhs coefficient by rhs coefficient and adds there exponents
        // ignores coefficients that are 0
        if (this->polyArray[i] != 0) {
            for (int j = 0; j < rhs.arraySize; j++) {
                productArray.polyArray[i + j] += (rhs.polyArray[j] * this->polyArray[i]);
            }
        }
    }
    // returns the product of lhs * rhs
    return productArray;
} // end of operator*


//------------ operator= ------------------------------
// Description: overloads = operator to utilize
// poly objects
//-----------------------------------------------------
const Poly &Poly::operator=(const Poly &rhs) {
    // if lhs == rhs (equivalent polynomials)
    if (this->polyArray == rhs.polyArray) {
        return *this;
    }
    // if lhs size == rhs size
    if (this->arraySize == rhs.arraySize) {
        //assigns lhs coefficient = rhs coefficient
        for (int i = 0; i < this->arraySize; i++) {
            this->polyArray[i] = rhs.polyArray[i];
        }
    } else {
        // This delete was breaking my code on Clion
        // but works fine on linux
        //delete[] this->polyArray; // delete lhs array
        this->polyArray = NULL;

        this->arraySize = rhs.arraySize; //sets lhs array size = rhs array size
        this->polyArray = new int[this->arraySize];

        // assigns values of rhs polynomial to lhs polynomial
        for (int i = 0; i < this->arraySize; i++) {
            this->polyArray[i] = rhs.polyArray[i];
        }
    }
    return *this;
} // end of operator=

//------------ operator== ------------------------------
// Description: overloads == operator to utilize
// poly objects
//-----------------------------------------------------
bool Poly::operator==(const Poly &rhs) const {
    // if polynomials are not equal in length
    if (this->arraySize != rhs.arraySize) {
        // if lhs > rhs
        if (this->arraySize > rhs.arraySize) {
            for (int i = 0; i < rhs.arraySize; i++) {
                // if coefficient values are not equivalent return false
                if (this->polyArray[i] != rhs.polyArray[i]) {
                    return false;
                }
            }
            for (int i = rhs.arraySize; i < this->arraySize; i++) {
                // checks if coefficient values are != 0
                if (this->polyArray[i] != 0) {
                    return false;
                }
            }
            return true;
        }
            // if lhs < rhs
        else {
            for (int i = 0; i < this->arraySize; i++) {
                // if coefficient values are not equivalent return false
                if (this->polyArray[i] != rhs.polyArray[i]) {
                    return false;
                }
            }
            for (int i = this->arraySize; i < rhs.arraySize; i++) {
                // checks if coefficient values are != 0
                if (rhs.polyArray[i] != 0) {
                    return false;
                }
            }
            return true;
        }
    }
    // if polynomials are equal length check each coefficient value too see
    // if they are equal.
    else {
        for (int i = 0; i < this->arraySize; i++) {
            // if coefficient values are not equivalent return false
            if (this->polyArray[i] != rhs.polyArray[i]) {
                return false;
            }
        }
    }
    // if lhs and rhs are equal in length and contain same coefficient values
    return true;
} // end of operator==

//------------ operator!= ------------------------------
// Description: overloads != operator to utilize
// poly objects
//-----------------------------------------------------
bool Poly::operator!=(const Poly &rhs) const {

    return !(*this == rhs);
} // end of operator!=

//------------ operator+= ------------------------------
// Description: overloads += operator to utilize
// poly objects
//-----------------------------------------------------
Poly &Poly::operator+=(const Poly &rhs) {
    *this = (*this + rhs);
    return *this;
}

//------------ operator-= ------------------------------
// Description: overloads -= operator to utilize
// poly objects
//-----------------------------------------------------
Poly &Poly::operator-=(const Poly &rhs) {
    *this = (*this - rhs);
    return *this;
}

//------------ operator*= ------------------------------
// Description: overloads *= operator to utilize
// poly objects
//-----------------------------------------------------
Poly &Poly::operator*=(const Poly &rhs) {
    *this = (*this * rhs);
    return *this;
}

