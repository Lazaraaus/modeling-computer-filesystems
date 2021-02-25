#include <iostream>
using namespace std;
#include "definitions.h"
#include "system_utilities.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>


int main () {
	char line[MAX_CMD_LINE_LENGTH];              //defining variables
	char *tokens[MAX_TOKENS_ON_A_LINE]; 
	ifstream inp; 

	inp.open("p4input.txt", ios::in);				//grabbing input file		
	if(inp.fail()) {
		cout<<"Brotato chip that file didn't load!!!";		//error message
			return 0;
	}

	int i = 0;
		int num_tokens;
		memset(line, NULL, MAX_CMD_LINE_LENGTH);         //memsetting line and tokens to null characters so function knows when to terminate
		memset(tokens, 0, 10);
	for (i; i<4; i++) {									//loop to loop through function and print all results while freeing up the space								
     	inp.getline(line, MAX_CMD_LINE_LENGTH);
		num_tokens = parseCommandLine(line, tokens);			
		memset(line, NULL, MAX_CMD_LINE_LENGTH);
	for (int k = 0; k<num_tokens; k++){
			cout<<tokens[k]<<"\n";
			free((void *)tokens[k]);
		} 
	cout<<endl;
	}
		

	system("PAUSE");
return 0;
}
