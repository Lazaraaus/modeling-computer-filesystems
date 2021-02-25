#include <iostream>
#include "disk_drive.h"
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

using namespace std;

void diskDrive::print()
{
	cout << "disk drive size: " << num_blocks*64 << "\n";   //print drive size
	cout <<"number of blocks: "<<num_blocks << "\n";     //print number of blocks
	cout << "size of map: " << ((num_blocks + 7)*sizeof(char))/8 <<"\n";  //print the size of the map
	cout << hex;   //convert to hex
	cout << "bitmap"<<" ";  //print bitmap
	for (int i = 0; i < (num_blocks+7)*sizeof(char)/8; i++) {
		int k = bitmap[i]; 
		k = k&0xff;
		cout <<k<<" "<<"\n";
	}

	cout<<dec;   //return to decimal format
}

int diskDrive::allocateBlock(int x)  //function to allocate blocks
{
	if ( x >= num_blocks | x < 0)
	{
		return BAD_BLOCK_NUMBER;
	}

	else{
	    int bitpos = x%8;
		int bytepos = x/8;

		char mask = 1<<bitpos;

		bitmap[bytepos] = bitmap[bytepos] | mask;
		return 0;
	}
}

int diskDrive::freeBlock(int y) //function to free blocks using masks
{
	if ( y >= num_blocks | y < 0)
	{
		return BAD_BLOCK_NUMBER;
	}
	else{
		int bitpos = y%8;
		int bytepos = y/8;

		char mask = ~(1<<bitpos);

		bitmap[bytepos] = bitmap[bytepos] & mask;
		return 0;

}
}

int diskDrive::isBlockFree(int z) //function checking if blocks are free
{
	if ( z >= num_blocks | z < 0)
	{
		return BAD_BLOCK_NUMBER;
	}
	else{
		int bitpos = z%8;
		int bytepos = z/8;
		char mask = 1<<bitpos;
		if (bitmap[bytepos] & mask) {
			return 0;
		}
		else
		{
			return 1;
		}

		

}
}

diskDrive::diskDrive(int num_bytes) //disk drive constructor
{
	num_blocks = (num_bytes + 63)/64;
    storage_block = (char *)malloc(sizeof(char) * num_bytes*64);
	bitmap = (char *)malloc(sizeof(char)*(num_blocks + 7)/8);
	memset(bitmap,0, (sizeof(char) *((num_blocks +7)/8)));


}

diskDrive::diskDrive() {   //default diskdrive constructor
}

diskDrive::~diskDrive(void) {   //diskdrive destructor
	free( (void *)bitmap);
	free ( (void *) storage_block);
}






