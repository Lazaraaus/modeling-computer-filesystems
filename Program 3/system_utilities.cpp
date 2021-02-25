/*

    Author:     Henschen
    Date:       January 28, 2013

*/
#include <iostream>
using namespace std;


#include "definitions.h"
#include "system_utilities.h"


void printError(int err) {
	
	switch(err) {
		case BAD_BLOCK_NUMBER:
		       cout << "***ERROR.  Bad block number encountered.\n";
		       break;
		default:
		       cout << "***ERROR.  Undetermined error encountered.\n";
	}

}