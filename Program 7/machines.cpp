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
	memcpy(copy, fd, 16);
	drive->retrieveBlock(buf , block);
	for (int i = 0 ; i < 16 ; i++)
	{
		buf[pos * 16 + i] = copy[i];
	}
	drive->storeBlock(buf, n);

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
	memcpy(fd, copy, 16);
	for (int i = 0 ; i < 16 ; i++)
	{
		copy[i] = buf[buf[pos] * 16 + i];
	}
	memcpy(fd, copy, 16);
}

void computer::print()  //print function of computer class
{
	cout<<name_2<<"\n";
	drive->print();
	
}

void computer::printDirectory()
{
	for (int k = 0; k< maximum_number_of_files; k++)
	{ 
		fileDescriptor *fd = new fileDescriptor;
		getFileDescriptor(k, fd); 
			
	if (fd->file_length == -1)
	cout<<"not in use";
	else
	cout<<"file name: "<<fd->file_name<<endl;
	cout<<" length: "<<fd->file_length<<endl;
	cout<<" first block on disk: "<<fd->block_number<<endl;
	}
}

int computer::createFile(char *n, int len)
{
	if (findFreeFileDescriptor() == FILE_SYSTEM_FULL)
		return FILE_SYSTEM_FULL;

	else {
	fileDescriptor *temp = new fileDescriptor();
	temp->file_length = len;
	memcpy(temp->file_name, n, sizeof(temp->file_name));
	putFileDescriptor(findFreeFileDescriptor(), temp);
	return 0;
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
}

PC::PC(char name[], int PC_drive, char owner[]) :computer(name, PC_drive, maximum_number_of_files)
{
	memset (owner_2, NULL, (sizeof(char) *32));
	memcpy(owner_2, owner, (sizeof(char) * 32));
	maximum_number_of_files = 8;
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