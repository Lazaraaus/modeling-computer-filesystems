#include <iostream>
#include "disk_drive.h"
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "machines.h"
using namespace std;

void printError(int err)    //function to print errors
{
	if (err = BAD_BLOCK_NUMBER){
		cout<<endl;
		cout<<"Wait Stop, brotato chip you have entered too big of a block number";
	}
	else {
		cout<< "Something went wrong";
	
	}
}