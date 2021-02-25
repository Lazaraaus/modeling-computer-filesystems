
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
#include "disk_drive.h"
#include "machines.h"
int errcount = 0;



int main() {

	char line[MAX_CMD_LINE_LENGTH];              //defining variables
	char *tokens[MAX_TOKENS_ON_A_LINE]; 
	ifstream inp; 

	inp.open("p8input.txt", ios::in);				//grabbing input file		
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
case SYSTEM_STATUS: cout<<"\n"<<"Check System Status"<<endl;
		systemStatus();			
	break;
case HALT: cout<<"I have halted"<<"\n"<<endl;
	break;
case ADD_NETWORK_NODE: cout<<"\n"<<"Adding Network Node";

	errcount = addNetworkNode(tokens, num_tokens);				   
	break;
case DELETE_NETWORK_NODE: cout<<"\n"<<"Deleting the network node: "<<endl;
	errcount = deleteNetworkNode(tokens, num_tokens);
	break;
case CREATE_FILE: cout<<"Creating... "<<endl;
	if (findNode(tokens[1]) != -1)
			{
				cout << "Recognized command to create file\n";						
				int numbytes = str2int(tokens[3]);							//converts string token to an int
				char *buf;
				buf = (char *) malloc(numbytes * sizeof(char));						//allocates space 
				for (int i = 0 ; i < numbytes ; i++)								//gets user input equal to number of bytes they specified
					buf[i] = inp.get();
				memset(buf + numbytes , NULL , sizeof(buf + numbytes) );			//cuts off extra memory 
				char *namebuf = new char;											//create buffer
				namebuf = (char *) malloc(sizeof(tokens[2]) -1);					//allocate enough space 
				memcpy(namebuf , tokens[2] , sizeof(namebuf));						//sets namebuf to filename
				errcount = network[findNode(tokens[1])]->createFile(namebuf , str2int(tokens[3]) , buf); //creates the file
			}
			else errcount = COMPUTER_NOT_FOUND;
			break;
case LS:  cout<<"Listing all the files...\n"<<endl;  
	if (findNode(tokens[1]) == -1)
		errcount = COMPUTER_NOT_FOUND;
	else {
		cout << "Recognized command to print directory:\n";
		network[findNode(tokens[1])]->printDirectory();
	}
	break;
case DELETE_FILES: cout<<"Deleting..."<<endl;
	break;
case PRINT_FILES: cout<<"Printing..."<<endl;
	if (findNode(tokens[1]) != -1)
			{
				cout << "Recognized command to print files:\n";
				network[findNode(tokens[1])]->printFiles(num_tokens , tokens);
			}
			else errcount = COMPUTER_NOT_FOUND;
	break;
case TRANSFER_FILE: cout<<"Transferring file to"<<endl;
	break;
case UNDEFINED_COMMAND: cout<<"There was no defined command"<<endl;
	break;
	
}

	} 
	
	while(getCommandNumber(tokens[0]) != HALT);

	
	
		
	
	system("PAUSE");
return 0;
printError(errcount);
}
