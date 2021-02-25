// Interface for basic machine class and its derived classes user,
// server and printer.


#ifndef MACHINE_CLASSES

#define MACHINE_CLASSES


#include "definitions.h"
#include "disk_drive.h"



class computer {

	// Basic machine objects

public:
	computer(char nm[], int disk_size);
	~computer(void);
	virtual void print(void);


protected:

	char         my_name[21];
	diskDrive    *my_disk;
};




#endif