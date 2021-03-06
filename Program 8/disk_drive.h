#ifndef DISK_DRIVE_H
#define DISK_DRIVE_H

class diskDrive {
public:
	diskDrive(int num_bytes); //constructor for diskDrive class//
	~diskDrive(void); //destructor for diskDrive class
	void print();   //print member function
	int allocateBlock(int x);  //allocateblock function
	int freeBlock(int y); //freeBlock function
	int isBlockFree(int z);  //isblockfree member function
	diskDrive(void);   //default constructor
	int storeBlock(char *d, int blk);
	int retrieveBlock(char *d, int blk);
	void formatDrive(int max_files);
	int findNBlocks(int n, int start);


private:
	int num_blocks;   //member variables
	char *bitmap;    
	char *storage_block;


};

#endif 