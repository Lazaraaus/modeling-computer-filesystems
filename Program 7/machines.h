#ifndef MACHINES_H
#define MACHINES_H
#include "disk_drive.h"

class computer {
public:
	computer(char name[21], int laptop_drive, int maximum_number_of_files); //constructor
	~computer(void); //destructor
	void print(); //print member function
	int isThisMyName(char *n);
	int maximum_number_of_files;
	void printDirectory();
	int createFile(char *n, int len);

protected:
	char name_2[21];  //name variable
	 diskDrive *drive; //disk drive pointer
	 int findFreeFileDescriptor();
	 void getFileDescriptor(int n, fileDescriptor *fd);
	 void putFileDescriptor(int n, fileDescriptor *fd);
	 
};

class PC: public computer {
public:
	PC();  
	PC(char name[32], int PC_drive, char owner[]); //constructor	
	~PC(void);				//destructor
	void print();			//print member function

private:
	char owner_2[32];  //owner name variable
};

class server: public computer {
public:
	server();
	server(char name[], int server_drive, char server_location[]);  //constructor
	~server(void);					//destructor
	void print();				// print member function
private:
	char server_location_2[16];		//location name variable

};

class printer: public computer {
public:
	printer();
	printer(char name[], int printer_drive, int num_printers);    //constructor
	~printer(void);				//destructor
	void print();				//print member function	
private:
	int num_of_printers;		//number of printer variable
};

#endif
