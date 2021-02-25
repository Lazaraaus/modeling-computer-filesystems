#include <iostream>
#include "disk_drive.h"
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "machines.h"
#include <stdio.h>

using namespace std;

computer::computer(char name[21], int laptop_drive)  //computer constructor
{
	memcpy(name_2, name, (sizeof(char) * 21));
    drive = new diskDrive(laptop_drive);
}

computer::~computer(void) //computer destructor
{
	
	delete drive;

}

void computer::print()  //print function of computer class
{
	cout<<name_2<<"\n";
	drive->print();
	
}