// ProDAgram2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>
using namespace std;

//Global Variables & Constants
const size_t arraySize{ 5 };
float coeff_x[arraySize];
float deriv_x[arraySize];

//Function Prototypes
int readPolynomial(float numbers[]); 
void displayPolynomial(int power, float coeff[]);
void derivativePolynomial(int power, float coeff[], float derivX[]);
float computePolynomial(int power, float coeff[], float xValue);
float exp(float a, float b); 

int main()
{
	//Generate Polynomial Array - Through a read file, hard coded, or by hand. 
	float numbers[5] = { 3, 1.5, 2.7, 3.1, 1.6};
	int xValue; 


	int power = readPolynomial(numbers); //Run the first function to populate the coeff_x array and find highest power of the polynomial
	cout << "Press any key to continue" << endl;
	cin.ignore();

	displayPolynomial(power, coeff_x);  //Run the second function to break down the polynomial into algebraic form
	cout << "Press any key to continue" << endl;
	cin.ignore();

	derivativePolynomial(power, coeff_x, deriv_x); //Run the third function to computer the derivatives of the polynomial
	cout << endl; 

	cout << "Please input an Xvalue to compute the polynomial with: "; 
	cin >> xValue; 
	cout << "You've entered: " << xValue;
	cout << " ...Press any key to continue" << endl;
	cin.ignore();
	computePolynomial(power, coeff_x, xValue); //Run the fourth function to compute the value of the polynomial for a given x value
	
	
}

//Functions for manipulating polynomials
	int readPolynomial(float numbers[]) {
		cout << "Reading the polynomial.." << endl; 
		int highestPower = numbers[0] ;
		for (unsigned int count{ 1 }; count <= highestPower + 1; ++count) {
			cout << setw(7) << "The value of coeff_x[" << count - 1 << "] is: " << coeff_x[count - 1];
			cout << setw(10) <<"  The value of numbers[" << count << "] is: " << numbers[count] << endl; 
			coeff_x[count - 1] = numbers[count]; 
			cout << "The value of coeff_x[" << count - 1 << "] after the operation is: " << coeff_x[count - 1] << endl;
			cout << endl; 
		
		}
		
		return highestPower;
		
	}

	void displayPolynomial(int power, float coeff[]) {
		cout << "Displaying Polynomial... "; 
		cout << "Press any key to continue" << endl; 
		cin.ignore(); 
		cout << endl; 
		cout << coeff[0]
			;
		for (unsigned int count{ 1 };  count <= power; ++count) {
			cout << " + " << coeff[count]; 
			for (unsigned int powerTrack{ 0 }; powerTrack < count; powerTrack++) {
				cout << "*x";
			}

		}
		cout << endl;
	}

	void derivativePolynomial(int power, float coeff[], float derivX[]) {
		for (unsigned int count{ 0 }; count <= power; count++) {
			derivX[power - count] = (coeff[power - count]) * (power - count); 
		}
		cout << "The derivative of the polynomial is... " << endl;
		displayPolynomial(power - 1, derivX); 
	}

	float computePolynomial(int power, float coeff[], float xValue) {
		float sum = coeff[0];
		for (int count{ power }; count > 0; count--) {
			sum = sum + ( coeff[count] * exp(xValue, count)); 
		}
		cout << "The value of the polynomial at X value = " << xValue << " is: " << sum;
		return sum; 
		
	} 

	float exp(float a, float b) {
		if (b == 1) {
			return a; 
		}
		else {
			float sum{ 1 };
			for (unsigned int count{ 0 }; count < b; count++) {
				sum *= a;
			}
			return sum;
		}
	}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
