#include <iostream>
#include "disk_drive.h"
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "machines.h"
#include <stdio.h>
#include <string>

using namespace std;

computer::computer(char name[], int laptop_drive, int maximum_number_of_files)  //computer constructor
{
	memset(name_2, NULL, (sizeof(char) *21));
	memcpy(name_2, name, (sizeof(char) * 21));
    drive = new diskDrive(laptop_drive);
}

computer::~computer(void) //computer destructor
{
	
	delete drive;

}

int computer::isThisMyName(char *n)
{
	if (strcmp(name_2, n) == 0)
		return 1;
	else
		return 0;
}

void computer::putFileDescriptor(int n, fileDescriptor *fd)
{
	int block; 
	int pos; 
	block = n/4;
	pos = n%4 ;
	char buf[64];
	char copy[16];
	memcpy(copy, fd, sizeof(fileDescriptor));
	drive->retrieveBlock(buf , block);
	for (int i = 0 ; i < 16 ; i++)
	{
		buf[pos * 16 + i] = copy[i];
	} 
	drive->storeBlock(buf, block);

}

void computer::getFileDescriptor(int n, fileDescriptor *fd)
{
	int block;																
	int pos; 
	block = n/4;																
	pos = n%4 ;
	char buf[64];
	char copy[16];
	drive->retrieveBlock(buf , block);											
	for (int i = 0 ; i < 16 ; i++)
	{
		copy[i] = buf[pos*16 + i];									
	} 
	memcpy(fd , (fileDescriptor *)copy , sizeof(fileDescriptor));
}

void computer::print()  //print function of computer class
{
	cout<<name_2<<"\n";
	drive->print();
	
}

void computer::printDirectory()
{
fileDescriptor *fd = new fileDescriptor;
	for (int i = 0 ; i < maximum_number_of_files ; i++)									//prints information of all files on disk_drive
	{
		getFileDescriptor(i , fd);
		if (fd->file_length == -1)
			cout << "file not currently in use \n";
		else cout << "file entry: " << i << " file name = " << fd->file_name << " length = " << fd->file_length << " first block on disk = " << fd->block_number << "\n";
	}
}

int computer::createFile(char *n, int len, char *ff)
{
	if (findFreeFileDescriptor() == FILE_SYSTEM_FULL)								//checks for unused fileDescriptors
		return FILE_SYSTEM_FULL;
	else
	{
		int firstblock;
		int numblocks = (len + 63)/64;
		firstblock = drive->findNBlocks(numblocks , maximum_number_of_files/4);		//finds firstblock on disk 
		if (firstblock == -1)
			return BAD_BLOCK_NUMBER;

		fileDescriptor *fd = new fileDescriptor();									//creates a fileDescriptor
		fd->file_length = len;														//sets the length , firstblock on disk , and name 
		fd->block_number = firstblock;													
		memset(fd->file_name , ' ' , sizeof(fd->file_name));
		memcpy(fd->file_name , n , sizeof(fd->file_name));
		putFileDescriptor(findFreeFileDescriptor(), fd);							//places fileDescriptor into drive
		char buf[64];																//buffer to store content 
		memset(buf , NULL , 64);													//sets to NULL to avoid any unused memory
		int indx = 0;																		
		int blocknum = 0;
		for (int i = 0 ; i < len ; i++)												//loops through 
		{	
			if (i < 64*(blocknum+1))												//if still in one block, sets values of buffer to equal those in ff
			{
				buf[indx] = ff[i];													//gets next value 
				indx = indx + 1;
			}
			else																	//if content in one block has been filled, stores values into diskdrive
			{
				drive->storeBlock(buf , firstblock + blocknum);
				blocknum += 1;														//increment blocknum 
				memset(buf , NULL , 64);											//set buf to NULL
				indx = 0;															//reset index 
				buf[indx] = ff[i];													//get next value	
				indx += 1;															//increment index
			}
			if (i == (len-1) )														//if end of content in file reached, store content into the block
				drive->storeBlock(buf , firstblock+blocknum);
		}
	}
	return 0;
		}

void computer::printOneFile(fileDescriptor fd)
{

	cout << "Printing file:" << (char *) fd.file_name << "\n";							//prints name
	int start , j ,blocks , length , count;												
	start = fd.block_number;																//first file on block
	length = fd.file_length;															//num  bytes in file
	blocks = (length + 63)/64;															//num blocks
	char *content;																		//holds the file contents
	char buf[64];																		//buffer to hold a block
	count = 0;
	j = 0;
	content = (char *) malloc(fd.file_length);
	for (int i = start ; i < (blocks+start) ; i++)										//loops from first block  to last block 
	{
		drive->retrieveBlock(buf , i);													//takes block
		while(j < 64)																	//puts content in block into buffer	
		{
			content[j] = buf[j];														//copies content inside block holding file contents
			cout << content[j];															//prints copy of file contents
			j += 1;
			if (count == (length-1))													//if reach end of file, break loop
				break;
			count += 1;
		}
		j = 0;
	}
	cout << "End of file. \n\n";
}

void computer::printFiles(int argc , char *argv[])
{
	fileDescriptor *fd = new fileDescriptor;							//holds fileDescriptor 
	int fnum;															//number of the fileDescriptor
	char buf[16];														//buffer 
	for ( int i = 2 ; i < argc ; i ++)									//loops through 
	{
		
		if (findFile(argv[i] , fd) == -1)								//checks if file is on the computer	
			cout << "File Not Found \n";								//print error if no such file
		else 
		{
			fnum = findFile(argv[i] , fd);								//places fileDescriptor into fd and fileDescriptor number into fnum
			fileDescriptor copy;										//copies fd to disk
			memcpy(buf , (char *) fd , sizeof(fileDescriptor) );		//places char version of fd into buffer
			copy = *(fileDescriptor *) buf;							//cast back to fileDescriptor and place into copyfd
			printOneFile(copy);										//prints out the information 
		}
	}
}

int computer::findFile(char *fname , fileDescriptor *fd)
{

	int block;																											
	block = maximum_number_of_files/4;								//position on block
	char buf[64];													//block buffer	
	char copy[16];													//fd buffer
	int fdnum = 0;													//number of the matching fileDescriptor	
	fileDescriptor *fdbuf = new fileDescriptor();					//fileDescriptor buffer	
	for (int i = 0 ; i < block ; i++)								//loop through number of blocks		
	{
		drive->retrieveBlock(buf , i);						        //gets block, puts in buffer value
		for (int j = 0 ; j < 3 ; j++)
			{
				fdbuf = (fileDescriptor *) buf + j;
				char *str = (char *) malloc(sizeof(fdbuf->file_name) +1);			//create pointer to compare with pointer of name of fileDescriptor we are searching for
				memset(str , NULL , sizeof(str) );
				memcpy(str , fdbuf->file_name , sizeof(str) );						//makes it 1 size larger to add the null character back to the 8 char sequence
				if (strcmp(str , fname) == 0 )										//if names are the same, then copies the copy into fd
				{
					memcpy(fd , fdbuf , sizeof(fileDescriptor));	
					return fdnum;													//returns fileDescriptor number
				
				fdnum += 1;
			}
	}
	return -1;																						//return -1 if none found
}
	
}

int computer::findFreeFileDescriptor()
{
		int index = 0;
	int iter = maximum_number_of_files /4;
	char buf[64] ;
	fileDescriptor *fd = new fileDescriptor;
	for (int i = 0 ; i <iter ; i++)									
	{
		drive->retrieveBlock(buf , i);									
		for (int pos = 0 ; pos < 4 ; pos++)
		{
			fd = (fileDescriptor *) buf + pos;							
				if (fd->file_length == -1)								
				{
					index =   pos + 4*i;								
					return index;
				}
		}
	}
	return FILE_SYSTEM_FULL;
}

PC::PC(char name[], int PC_drive, char owner[]) :computer(name, PC_drive, maximum_number_of_files)
{
	memset (owner_2, NULL, (sizeof(char) *32));
	memcpy(owner_2, owner, (sizeof(char) * 32));
	maximum_number_of_files = 8;
	drive->formatDrive(maximum_number_of_files);
}

PC::~PC(void) //:computer(name, PC_drive)
{
	delete drive;
}

void PC::print()  
{
	cout<<owner_2<<" ";
	computer::print();
}



server::server(char name[], int server_drive, char server_location[16]) :computer(name, server_drive, maximum_number_of_files)
{
	memset (server_location_2, NULL,(sizeof(char) * 16));
	memcpy(server_location_2, server_location, (sizeof(char) *16));
	maximum_number_of_files = 16;
	drive->formatDrive(maximum_number_of_files);
}

server::~server(void)
{
	delete drive;
}

void server::print()
{
	cout<<server_location_2<<endl;
	computer::print();
	
}

printer::printer(char name[], int printer_drive, int num_printers) :computer(name, printer_drive, maximum_number_of_files)
{
	drive = new diskDrive(printer_drive);
	num_of_printers = num_printers;
	maximum_number_of_files = 16;
	drive->freeBlock(maximum_number_of_files);
}

printer::~printer(void)
{
	delete drive;
}

void printer::print()
{
	cout<<"number of printers: "<<num_of_printers<<endl;
	computer::print();
	
}