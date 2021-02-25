#include <iostream>
#include "definitions.h"
using namespace std;
#include <fstream>
#include "system_utilities.h"
#include "machines.h"
#include <string.h>
#include <stdio.h>

int wait() 
{
	cout << "Press any key to continue...";
cin.get();
return 0;
}
int length = 9;
int str2int(char *string)
{
	#define CHAR_TO_INT 48
	int i;
	int num = 0;
	int digits = strlen (string);
	int magnitude = 1;

	for (i = (digits - 1); i >= 0; i--)
	{
		num += (string [i] - CHAR_TO_INT) * magnitude;
		magnitude *= 10;
	}

	return num;
}

class commandElement {
	//command element class
public:   
	commandElement(char *command1, int commandRep1); //constructor
    int amIThisCommand(char *command1);
	char *command;
	int commandRep;
};

commandElement::commandElement(char *command1, int commandRep1) {
	commandRep = commandRep1;
	command  = (char *)malloc(strlen(command1)+1);
	memset(command, NULL, strlen(command1)+1);
	(char *)memcpy(command, command1, (strlen(command1)+1));
}

 int commandElement::amIThisCommand(char *command1){
	 //function to compare strings, and find command value
	if (strcmp(command1, command) == 0)  
		return commandRep;
	else
		return 0;
}

int parseCommandLine(char x[MAX_CMD_LINE_LENGTH], char *y[MAX_TOKENS_ON_A_LINE])
{
	int i = 0;    
	int token_count = 0;											//DECLARATIONS	
	char char_list[256];			
	int count = 0;
	int next_token = 0;


	if (x[i] != NULL)											//FIST IF STATEMENT TO CHECK FOR NULL CHARS
	{
		 while(x[i] != NULL)									//FIRST WHILE LOOP 
			if(x[i] == '"')
			{ 
				memset(char_list, NULL, MAX_CMD_LINE_LENGTH);      
				count = 0;
				i++;

				while (x[i] != '"' && x[i] != NULL)             //NESTED WHILE LOOP TO CHECK FOR "

				{
					char_list[count] = x[i];
					count++;
					i++;
				}
				count++;
				y[token_count] = (char *)malloc(count);			//ALLOCATING MEMORY FOR THE STORED TOKENS
				memcpy(y[token_count], char_list, count);
				token_count = token_count + 1;
				i++;
			
			}
			else if(x[i] != ' ')								//ELSE IF CHECKING FOR BLANK SPACES
			{    
				memset(char_list, NULL, MAX_CMD_LINE_LENGTH);
				count = 0;
				while(x[i] != ' ' && x[i] != NULL)				//2ND NESTED WHILE LOOP
				{
					
				char_list[count]=x[i];
					count++;
					i++;
				}
				count++;
				y[token_count] = (char *)malloc(count);				//ALLOCATING MEMORY FOR THE STORED TOKENS
				memcpy(y[token_count], char_list, count);
				i++;
				token_count = token_count + 1;
				
			}

			else 
			{ 
				i++;
			}

		
	}
	else {
		cout<< "Woah there brotato chip there's nothing here!"<<"\n";		//ERROR MESSAGES
	}

		

//	cout<<"Number of tokens:"<<" "<<token_count<<"\n";	

return token_count;

}
static commandElement *commandList[NUMBER_OF_COMMANDS]; //array of possible commands
void fillCommandList(void){
	//fills the commandList
	commandList[0] = new commandElement("system_status", SYSTEM_STATUS);
	commandList[1] = new commandElement("halt", HALT);
	commandList[2] = new commandElement("add_network_node", ADD_NETWORK_NODE);
	commandList[3] = new commandElement("delete_network_node", DELETE_NETWORK_NODE);
	commandList[4] = new commandElement("create_file", CREATE_FILE);
	commandList[5] = new commandElement("ls", LS);
	commandList[6] = new commandElement("delete_files", DELETE_FILES);
	commandList[7] = new commandElement("print_files", PRINT_FILES);
	commandList[8] = new commandElement("transfer_file", TRANSFER_FILE);
}
int getCommandNumber(char *s) 
	 {
		 //gets the command number for the switch statement
		int i = 0;
		for (i; i<9; i++)
		{
			if (commandList[i]->amIThisCommand(s) != 0)
				return commandList[i]->amIThisCommand(s);
		}
		return UNDEFINED_COMMAND;
	}
 computer *network[MAX_NETWORK_NODES]; //array of computers simulating network

int m = 0;
int findNode(char *n) 
{
	//finds nodes, used in the delete node function
	
	for (int i = 0; i<length; i++)
	{
		if (network[i]->isThisMyName(n) != 0)
			return i;
		if (network[i]->isThisMyName(n) == 0)
			return -1;
	}
	return -1;
}
int addNetworkNode(char *toks[], int numberToks)
{
	//adds nodes to the network
	
	char *pc = "PC";
	char *server_char = "server";
	char *printer_char = "printer";
	if (m>9)
	{
		cout<<"\n"<<"Oh no the network has reached it's limit."<<"\n"<<endl;
		return NETWORK_FULL;
	}
	else if (strcmp(toks[1], pc) == 0)
	{
		cout<<endl;
		 PC *pc1;
		 pc1 = new PC(toks[2], str2int(toks[3]), toks[4]);
		 pc1->print();
		 cout<<"\n";
		 cout<<endl;
		 network[m] = pc1;
		 cout<<m;
		 m++;
	
		return 0;
	}
	else if (strcmp(toks[1], printer_char) == 0 )
	{
		cout<<endl;
		 printer *p1;
		 p1 = new printer(toks[2], str2int(toks[3]), str2int(toks[4]));
		 p1->print();
		 cout<<"\n";
		 cout<<endl;
		 network[m] = p1;
		 cout<<m;
		 m++;
		
		 return 0;
	}

	else if(strcmp(toks[1], server_char) == 0)
	{
		cout<<endl;
	  server *s1;
	  s1 = new server(toks[2], str2int(toks[3]), toks[4]);
	  s1->print();
	  cout<<"\n";
	  cout<<endl;
	  network[m] = s1;
	  cout<<m;
	  m++;
		return 0;
	}
	else 
	{
		cout<<endl;
	cout<<"Oh noes invalid type"<<endl;

	return INVALID_COMPUTER_TYPE;
} 
	

}

int deleteNetworkNode (char *toks[], int numberToks)
{
	//finds, and deletes a node.
	if (findNode(toks[1]) != -1)
	{
		
		int a;
		a = findNode(toks[1]);
		network[a] = NULL;
		delete network[a];
	for (int i = a; i < length; i++) {
			network[i] = network[i + 1];
	}
			cout<<"\n"<<"Deleted"<<endl;
	network[length] = NULL;
	length--;
	m = length;
			
	   return 0;
	}
	
	else
		return COMPUTER_NOT_FOUND;
}
void systemStatus()
{
	//systemStatus causes all computers in the network to print out their information.
	cout<<"\n";
	cout<<"The current nodes on this network are: "<<"\n"<<endl;
	int o = 0;
	for (o; o<m; o++) {
		cout<<"\n"<<endl;
	network[o]->print();
	} 
	cout<<"\n";
	cout<<endl;
	wait();
}
void printError(int err)
{
	//Print error function to find if errors are running rampant.

	switch (err)     
	{
	case 200: cout <<"invalid block number";
				  break;
	case 201: cout<<"The network is beyond full";
				  break;
	case 202: cout<<"That computer wasn't found in the network";
				  break;
	case 203: cout<<"This is not a valid computer type";
				  break;
	case 99: cout<<"This command was highly undefined";
				 break;

	default: cout<<"something has failed for one reason or another";
		break;
	}
}