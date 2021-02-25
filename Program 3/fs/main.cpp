

#include <iostream>
using namespace std;
#include "definitions.h"
#include "disk_drive.h"
#include "machines.h"
#include "system_utilities.h"

int main() {
	// Test driver for EECS 211 Program 3.
	 //Written by L. Henschen

	int errno;

	diskDrive d1(1000), *d2;
	computer c1("Larry's laptop", 2000), 
	     *c2,
		 c3("test", 127);

	d2 = new diskDrive(512);
	c2 = new computer("12345678901234567890", 200);


	d1.print();
	cout << "\n\n";

	d2->print();
	cout << "\n\n";

	errno = d1.allocateBlock(1);
	if(errno!=0) printError(errno);
	errno = d1.allocateBlock(7);
	if(errno!=0) printError(errno);
	errno = d1.allocateBlock(8);
	if(errno!=0) printError(errno);
	errno = d1.allocateBlock(12);
	if(errno!=0) printError(errno);
	errno = d1.allocateBlock(16);
	if(errno!=0) printError(errno);
	errno = d1.allocateBlock(-1);
	if(errno!=0) printError(errno);

	errno = d2->allocateBlock(0);
	if(errno!=0) printError(errno);
	errno = d2->allocateBlock(2);
	if(errno!=0) printError(errno);
	errno = d2->allocateBlock(4);
	if(errno!=0) printError(errno);
	errno = d2->allocateBlock(6);
	if(errno!=0) printError(errno);

	cout << "\n\n";
	d1.print();
	cout << "\n\n";
	d2->print();

	cout << "\n\n";
	for(int i=0; i<17; i++) {
		cout << "Disk 1 block " << i;
		errno = d1.isBlockFree(i);
		if(errno==BAD_BLOCK_NUMBER) printError(errno);
		else if(errno) cout << " free\n";
		else           cout << " allocated\n";
	}

	
	d1.freeBlock(1);
	d1.freeBlock(7);
	d1.freeBlock(8);
	d1.freeBlock(12);
	d1.freeBlock(16);
	d1.freeBlock(-1);

	d2->freeBlock(0);
	d2->freeBlock(4);

	

	cout << "\n\n";
	d1.print();
	cout << "\n\n";
	d2->print();
	
	cout << "\n\n";
	c1.print();
	cout << "\n\n";
	c2->print();
	cout << "\n\n";
	c3.print();

//	delete d2;
//	delete c2;

	
	
	cout << "That's all, folks.";
	int f;
	cin>>f;
	return 0;

	
}


	