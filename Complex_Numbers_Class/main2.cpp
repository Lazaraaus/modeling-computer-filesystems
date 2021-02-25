/*

    Author:   Henschen
    Date:     January 29, 2013
    
    Example of a simple class - COMPLEX

*/

#include <iostream>
using namespace std;

#include "COMPLEX.h"


int main(void) {

	complex c1, c2(5.1, 3.2), d[10];  int i;

	for(i=0; i<10; i++) d[i].cset(i,i);

	for(i=0; i<10; i++) d[i].print();

	c1 = d[3].cadd(d[5]);
	c1.print();
	c2 = d[8].cadd(c1);
	c2.print();

	return 0;
}