//Author:    Patrick Taliaferro
//Date:      May 8, 2020
//File Name: main.cpp


#include <iostream>
#include <fstream>


int main(int argc, char * argv[]) {
	
	if(argc < 4) return 0;

	unsigned long ulOccuranceCount = 0; 
	unsigned short usLengthOfReplacedString = 0;
	unsigned short usLengthOfReplacingString = 0;
	unsigned long ulSizeOfFile = 0;

	while(argv[2][usLengthOfReplacedString] != '\0') usLengthOfReplacedString++;
	while(argv[3][usLengthOfReplacingString] != '\0') usLengthOfReplacingString++;

	std::ifstream ifs(argv[1],std::ifstream::in);
	
	ifs.seekg(0,ifs.end);
	ulSizeOfFile = ifs.tellg();
	ifs.seekg(0);

	char * cBuffer = new char[ulSizeOfFile];

	ifs.read(cBuffer,ulSizeOfFile);

	ifs.close();

	if (remove(argv[1]) == 0) std::cout << "Deleted Successfully\n";
	else 
	{
		std::cout <<"remove() unsuccessful\n"; //rewrite 
		return 0; 
	}

	
	//create new file and copy in cBuffe
	std::ofstream ofs(argv[1],std::ofstream::out);
	int j;

	for(int i = 0; i < ulSizeOfFile - usLengthOfReplacedString; i++)
	{
		if(cBuffer[i] == argv[2][1])
		{
			j = 1;
			while(j <= usLengthOfReplacedString && cBuffer[i+j] == argv[2][j+1]) j++;		
		}
		if(j > usLengthOfReplacedString)
		{
			ofs.write(argv[3],usLengthOfReplacingString);
			i += usLengthOfReplacedString;
			i--;
			ulOccuranceCount++;
		}
		else ofs.put(cBuffer[i]);
	}

	//print out how many occurances there were
	std::cout << "Number of Changes: " << unsigned(ulOccuranceCount) << "\n";
	ofs.close();

	delete cBuffer;
	return 0;
}
