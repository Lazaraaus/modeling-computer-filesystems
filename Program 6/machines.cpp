#include <iostream>
#include "disk_drive.h"
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "machines.h"
#include <stdio.h>
#include <string>

using namespace std;

computer::computer(char name[], int laptop_drive)  //computer constructor
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

void computer::print()  //print function of computer class
{
	cout<<name_2<<"\n";
	drive->print();
	
}

PC::PC(char name[], int PC_drive, char owner[]) :computer(name, PC_drive)
{
	memset (owner_2, NULL, (sizeof(char) *32));
	memcpy(owner_2, owner, (sizeof(char) * 32));
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



server::server(char name[], int server_drive, char server_location[16]) :computer(name, server_drive)
{
	memset (server_location_2, NULL,(sizeof(char) * 16));
	memcpy(server_location_2, server_location, (sizeof(char) *16));
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

printer::printer(char name[], int printer_drive, int num_printers) :computer(name, printer_drive)
{
	drive = new diskDrive(printer_drive);
	num_of_printers = num_printers;
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