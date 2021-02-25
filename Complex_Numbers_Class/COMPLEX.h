/*

    Author:   Henschen
    Date:     January 29, 2013
    
    Example of a simple class - COMPLEX
    
    This file is the header file that contains the class declaration.

*/




#ifndef COMPLEX_H
#define COMPLEX_H

class complex {

public:
	complex();
	complex(float r, float i);
	complex cadd(complex v2);
	void    cset(float rr, float ii);
	void    print(void);
	

private:
	float real_part;
	float imaginary_part;
};


#endif
