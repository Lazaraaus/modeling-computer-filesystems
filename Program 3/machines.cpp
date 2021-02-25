// Implementation for the machine and derived classes user, servere,
// and printer.

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#include "machines.h"



computer::computer(char nm[], int disk_size) {

	strncpy(my_name, nm, sizeof(my_name));
	my_name[19] = 0;     // In case name was too long

	// Minimum disk size is 128, so check the input parameter for validity.
	if(disk_size<128) disk_size = 128;         // If too small, reset to default minimum.
	my_disk = new diskDrive(disk_size);        // Dynamically create the drive.

	return;
}


computer::~computer(void) {

	delete my_disk;

	return;
}


void computer::print(void) {

	cout << "machine:  " << my_name << "\n";
	my_disk->print();

	return;
}


