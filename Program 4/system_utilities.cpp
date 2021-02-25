#include <iostream>
#include "definitions.h"
using namespace std;
#include <fstream>
const char* DELIMITER = " ";

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

		

	cout<<"Number of tokens:"<<" "<<token_count<<"\n";	

return token_count;

}
