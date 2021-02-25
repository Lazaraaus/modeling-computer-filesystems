// Declaration of the class disk_drive.


#ifndef DISK_DRIVE

#define DISK_DRIVE



class diskDrive{

	// A mass storage device with disk_size bytes organized into
	// 64-byte blocks.  Data member storage points to the dynamically
	// allocated storage area.  Data member block_map is a bit map
	// indicating which blocks are free (0 bit) or in use (1 bit).

public:


	diskDrive(int size=1024);
	~diskDrive(void);
	int  isBlockFree(int n);
	void print(void);
	int allocateBlock(int blk);
	int freeBlock(int blk);



private:
	int  disk_size;       // Number of blocks on the disk.
	char  *block_map;     // Points to the data storage.
	char  *storage;       // Points to the bit map that tells which blocks are free.


};

#endif