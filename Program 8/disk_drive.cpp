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
		cout <<k<<" "<<" ";
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
	int bytepos = 0;
	int bitpos = 0;
	char mask = NULL;
	
	bytepos = z/8;
	bitpos = z%8;
	mask = 1 << bitpos;
	if (z >= num_blocks || z <0)              
		return BAD_BLOCK_NUMBER;            //return BAD_BLOCK_NUMBER if not in range
	else
		{if (bitmap[bytepos] & mask)        //return 0 if not free (allocated)
			return 0;
		else
			return 1;                       //return 1 if free
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

int diskDrive::storeBlock(char *d, int blk) 
{
	if (blk >= num_blocks) 
	{
		return BAD_BLOCK_NUMBER;
	}
	else
	{
		memcpy((storage_block + 64*blk), d, 64);
		return 0;
	}
	
}

int diskDrive::retrieveBlock(char *d, int blk)
{
	if (blk >= num_blocks) 
	{
		return BAD_BLOCK_NUMBER;
	}
	else
	{
		memcpy(d, &storage_block[64*blk], 64);
		return 0;
	}
	return 0;
}

void diskDrive::formatDrive(int max_files)
{
	fileDescriptor *fd = new fileDescriptor(); 
	memset(fd->file_name, 0, sizeof(fd->file_name));
	fd->file_length = -1;
	fd->block_number = 0;
	int blocks;
	blocks = max_files/4;

for (int i = 0 ; i < num_blocks ; i++)
	{
		freeBlock(i);															//unallocates all blocks
	}
	for (int i = 0 ; i < max_files ; i++)										//copies default into storagespace
	{
		memcpy(storage_block +16*i , (char *)fd , sizeof(fileDescriptor));
		
	}
	for (int i = 0 ; i< blocks ; i++)
		allocateBlock(i);
}

int diskDrive::findNBlocks(int n, int start)
{
int i , done , j;										//loop counting variables
	i = start;												//i is block number
	j = 0;													//j is iteration of the sequence	
	done = 0;												//variable to see if n free contiguous blocks found
	while ( i <	num_blocks)									//loops through all the blocks
	{
		while(j < n)										//nested loop loops through n times
		{
			if (isBlockFree(i + j) == 0 )					//checks if block and next (n-1) blocks are not free
			{
				i = i + j + 1;								//sets i to be index of next block to check
				done = 0;									//resets counters
				j=0;
			}
			else 
			{
				done += 1;									//if free, adds 1 to done and to iteration
				j += 1;
				if (done == n)
					return i;								//returns index of first free block if n free contiguous blocks are found
			}
		}
	}
	return -1;												//returns -1 if sequence not found
}




