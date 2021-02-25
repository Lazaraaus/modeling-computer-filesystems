#ifndef MACHINES_H
#define MACHINES_H

class computer {
public:
	computer(char name[21], int laptop_drive); //constructor
	~computer(void); //destructor
	void print(); //print member function

private:
	char name_2[21];  //name variable
	 diskDrive *drive; //disk drive pointer
};
#endif
