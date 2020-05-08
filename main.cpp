//Author:    Patrick Taliaferro
//Date:      May 8, 2020
//File Name: main.cpp


#include <iostream>
#include <fstream>


int main(int argc, char * argv[]) {
	
	if(argc < 4) return 0;

	unsigned long ulOccuranceCount = 0; 
	unsigned short usLengthOfReplacedString = 0;
	unsigned long ulSizeOfFile = 0;

	while(argv[2][usLengthOfReplacedString] != '\0') usLengthOfReplacedString++;

	std::ifstream ifs(argv[1],std::ifstream::in);
	
	while(ifs.get()) ulSizeOfFile++;

	char * cBuffer = new char[ulSizeOfFile];

	//Read out file into cBuffer, Finding first substring and replacing it
	//delete old file
	//create new file and copy in cBuffer
	//print out how many occurances there were


	ifs.close();
	delete cBuffer;
	return 0;
}
