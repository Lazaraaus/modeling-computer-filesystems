/*   Averaging program with input from a file or keyboard.
    Author:  Yjaden Wood
             EECS 211, Winter 2013, Program 1


    File input is of the form:  N (number of scores in set) followed by
                                N numbers folowed by
                                -1 (there is another set) or -2 (end of data)


*/

#include <iostream>
#include <fstream>
using namespace std;

// Set the following constant to 1 for input from the keyboard,
// 0 for input from file.
#define DEBUG 0
int getOneNumber(int src);

// This is the input file for when DEBUG is 0.
ifstream inFile;

int main() {
	// Your variables go here.  Be sure to include an int called more.
	int more = 0;
	int cmd = -1;
	int count = 0;
	// Sum of data set
	int sum = 0;
	// Average of data set
	float avg = 0;
	// Next score
	int sec_input = 0;
	// Number of scores
	int number = 0;
	// Number of invalid scores
	int error = 0;
	
	// Checks if read file is set, checks for text file, generates error message and exits program if no text file found
	if(DEBUG==0) {
		inFile.open("p1input.txt", ios::in);
		if(inFile.fail()) {
			cout << "Could not open input file.  Program terminating.\n\nEnter an integer to quit.";
			cin >> more;
			return 0;
		}
	}
	
	while (cmd !=-2 && cmd == -1)
	{
		// resets vars
		count = 0;
		sum = 0;
		number = 0;
		error = 0;
		
		// number of scores in dataset
		cmd = getOneNumber(DEBUG);		
		
		// loop that executes a finite number of times
			while (count<cmd )
			{
			// gets next score in set
			sec_input = getOneNumber(DEBUG);
		
			// checks if score is between [0,100] 
			if ((sec_input >= 0) && (sec_input <=100))
			{
				// adds scores
				sum = sum + sec_input;
				// increments counter 
				number++;
			}
			else{
				// increments count for invalid scores
				error = error +1;
			}
			
			count = count+1;
			}
			
			// checks if 0 scores were entered
			
			if (cmd == 0 )
				cout << "No valid scores\n\n";
			// if more than 0 scores were entered, average is computed
			else{
				avg = (float)sum/number;
				// if more than one valid score, will print average and number of facetious scores
				if (error != cmd){
					cout << avg <<". ";
					cout << "Number of invalid scores: " << error << ". \n\n";
				}
				// display error message if no valid scores entered
				else cout << "No valid scores\n\n";
			}
			
			// input -1 or -2 to either continue or terminate program
			cmd = getOneNumber(DEBUG);
	}

	// message once averages have been computed
	cout << "End of data sets.  Enter an integer to quit.\nHave a nice day!";
	// user inputs ends program
	cin >> more;
	return 0;
}

int getOneNumber(int src) {
	// Gets the next integer from the input.  If src is
	// 0, then read from the file opened in the main function,
	// otherwise read from the keyboard.

	int val;

	if(src) {
		// Input from keyboard.

		cout << "Enter the next input: ";
		cin >> val;
	}
	else {
		// Input from file.
		inFile >> val;
	}

	return val;
}