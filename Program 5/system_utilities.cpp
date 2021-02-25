#include <iostream>
#include "definitions.h"
using namespace std;
#include <fstream>
#include "system_utilities.h"




class commandElement {
public:   
	commandElement(char *command1, int commandRep1); //constructor
    int amIThisCommand(char *command1);
	char *command;
	int commandRep;
};

commandElement::commandElement(char *command1, int commandRep1) {
	commandRep1 = commandRep;
	command  = (char *)malloc(strlen(command1)+1);
	(char *)memcpy(command, command1, strlen(command1 + 1));
}

 int commandElement::amIThisCommand(char *command1){
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

				while (x[i] != '"' & x[i] != NULL)             //NESTED WHILE LOOP TO CHECK FOR "

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
				while(x[i] != ' ' & x[i] != NULL)				//2ND NESTED WHILE LOOP
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

static commandElement *commandList[NUMBER_OF_COMMANDS];
void fillCommandList(void){
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
		int i = 0;
		for (i; i<9; i++)
		{
			if (commandList[i]->amIThisCommand(s) == 0)
				return commandList[i]->amIThisCommand(s);
		}
		return UNDEFINED_COMMAND;
	}