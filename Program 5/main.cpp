
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




int main() {
int a;

	char line[MAX_CMD_LINE_LENGTH];              //defining variables
	char *tokens[MAX_TOKENS_ON_A_LINE]; 
	ifstream inp; 

	inp.open("p5input.txt", ios::in);				//grabbing input file		
	if(inp.fail()) {
		cout<<"Brotato chip that file didn't load!!!";		//error message
			return 0;
	}

	fillCommandList();
	do {
	int i = 0;
		int num_tokens;
		memset(line, NULL, MAX_CMD_LINE_LENGTH);         
		memset(tokens, 0, 10);														
     	inp.getline(line, MAX_CMD_LINE_LENGTH);
		num_tokens = parseCommandLine(line, tokens);			
		memset(line, NULL, MAX_CMD_LINE_LENGTH);

		switch(getCommandNumber(tokens[0])) {
case SYSTEM_STATUS: cout<<"Check System Status"<<endl;
					cout<<"The tokens were";
	break;
case HALT: cout<<"I have halted";
	break;
case ADD_NETWORK_NODE: cout<<"Adding Network Node"<<endl;
					   cout<<"The tokens were";
	break;
case DELETE_NETWORK_NODE: cout<<"Deleting the network node: "<<endl;
			break;
case CREATE_FILE: cout<<"Creating... "<<endl;
	break;
case LS:  cout<<"Listing all the files..."<<endl;
	break;
case DELETE_FILES: cout<<"Deleting..."<<endl;
	break;
case PRINT_FILES: cout<<"Printing..."<<endl;
	break;
case TRANSFER_FILE: cout<<"Transferring file to"<<endl;
	break;
case UNDEFINED_COMMAND: cout<<"There was no defined command"<<endl;
	break;
	
}
for (int k = 0; k<num_tokens; k++){
			cout<<tokens[k]<<"\n";
	
		} 

	}

	while(getCommandNumber(tokens[0]) != HALT);



	
	
		

	system("PAUSE");
return 0;
}
