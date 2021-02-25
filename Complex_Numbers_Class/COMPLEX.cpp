/*

    Author:   Henschen
    Date:     January 29, 2013
    
    Example of a simple class - COMPLEX
    
    This file is the cpp file that contains the class implementation.

*/


#include <iostream>
using namespace std;

#include "COMPLEX.h"


complex::complex() {
	real_part = 0.0;
	imaginary_part = 0.0;
}

complex::complex(float r, float i) {
	real_part = r;
	imaginary_part = i;
}

complex complex::cadd(complex v2) {
	complex temp;

	temp.real_part      = real_part      +   v2.real_part;
	temp.imaginary_part = imaginary_part +   v2.imaginary_part;

	return temp;
}

void complex::cset(float rr, float ii) {
	real_part = rr;
	imaginary_part = ii;

	return;
}

void complex::print(void) {

	cout << "(" << real_part << "," << imaginary_part << ")\n";
	return;
}
