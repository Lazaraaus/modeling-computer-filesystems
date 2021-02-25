// Implementation of the class disk_drive

#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "definitions.h"
#include "disk_drive.h"

// Set the size of one storage block.
#define BLOCK_SIZE   64

diskDrive::diskDrive(int size) {
	int size_of_map;

	disk_size = (size+BLOCK_SIZE-1)/BLOCK_SIZE;     // Number of blocks - round up

	size_of_map = (disk_size+7)/8;                  // Number of bytes in the map - round up
	block_map = (char *)malloc(size_of_map);
	memset(block_map, 0, size_of_map);              // Set all bits to 0
	
	storage   = (char *)malloc(disk_size*BLOCK_SIZE);

	return;
}


diskDrive::~diskDrive(void) {

	free((void *) block_map);
	free((void *) storage);

	return;
}



int diskDrive::isBlockFree(int n) {
	// Return 1 if block n is free, 0 if it is not free.

	int offset;             // The byte index for the bitmap array
	int shift_count;        // The bit position within the byte in the bitmap array
	char msk;

	if((n<0) || (n>=disk_size)) {
		// Ignore if not a valid block.
		//cout << "    Is-free error: invalid block number.\n";
		return BAD_BLOCK_NUMBER;
	}

	offset = n/8;                  // This is the index to the byte we need.
	shift_count = n - (offset*8);
	msk = (1<<shift_count);
	if(block_map[offset] & msk) return 0;  // If bit is 1, then block is not free
	else                        return 1;  // If bit is 0, block is free

}



void diskDrive::print(void) {
	// Print size, number of blocks and block map.

	int j, size_of_map, tmp;

	size_of_map = (disk_size+7)/8;
	cout << "  Disk_drive:  disk_size = " << disk_size*64 << "\n";
	cout << "        number_of_blocks = " << disk_size << "\n";
	cout << "             size_of_map = " << size_of_map << "\n";

	cout << hex;                      // Set for HEX mode for map
	cout << "               Memory map: ";
	for(j=0; j<size_of_map; j++) {
		// Because bitmap is declared as char, we need to convert
		// to int so cout will not treat it as a code for a character.
		tmp = block_map[j];        // Convert to int - extends to 32 bits.
		tmp &= 0xff;               // Mask off the extended bits.
		cout << tmp << "  ";
	}
	//cout << "\n\n\n";
	cout << "\n" << dec;          // Set back to decimal output


	return;
}



int diskDrive::allocateBlock(int blk) {
	// Set the bit in block_map corresponding to blk.
	// Calculate which byte has the bit, and then left shift a
	// 1 to the correct position.

	int offset, shift_count;    // See isBlockFree for description of the variables used.
	char msk;

	if((blk<0) || (blk>=disk_size)) {
		// Ignore if not a valid block.
		//cout << "    Allocate error: invalid block number.\n";
		return BAD_BLOCK_NUMBER;
	}

	offset = blk/8;              // This is the index to the byte we need.
	shift_count = blk - (offset*8);
	msk = (1<<shift_count);
	block_map[offset] |= msk;

	return 0;
}


int diskDrive::freeBlock(int blk) {
	// Clear the bit in block_map corresponding to blk.
	// Calculate which byte has the bit, and then left shift a
	// 1 to the correct position.

	int offset, shift_count;    // See isBlockFree for description of the variables used.
	char msk;

	if((blk<0) || (blk>=disk_size)) {
		// Ignore if not a valid block.
		//cout << "    Free-block error: invalid block number.\n";
		return BAD_BLOCK_NUMBER;
	}

	offset = blk/8;              // This is the index to the byte we need.
	shift_count = blk - (offset*8);
	msk = (1<<shift_count);
	block_map[offset] &= (~msk);

	return 0;
}


