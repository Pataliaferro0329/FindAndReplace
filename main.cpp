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

	if (remove(argv[1]) != 0)
	{
		std::cout <<"ERROR: File work error - remove(<File_Name>) != 0\n";
	       	std::cout <<"Most Likely due to not high enough priveleges\n"; 
		return 0; 
	}

	//for(int i = 0; i < ulSizeOfFile; i++) std::cout << cBuffer[i];	
	
	std::ofstream ofs(argv[1],std::ofstream::out);
	int j;

	std::cout << "\nStart Parsing\n";

	for(int i = 0; i < ulSizeOfFile - usLengthOfReplacedString; i++)
	{
		j = 1;
		if(cBuffer[i] == argv[2][0])
		{
			while(j < usLengthOfReplacedString && cBuffer[i+j] == argv[2][j]) j++;		
		}
		//std::cout << cBuffer[i] << " : " << j << "\n";
		if(j == usLengthOfReplacedString)
		{
			ofs.write(argv[3],usLengthOfReplacingString);
			i += usLengthOfReplacedString - 1;
			ulOccuranceCount++;
			//for(int k = 0; k < usLengthOfReplacedString; k++) std::cout << argv[3][k];
		}
		else 
		{
			ofs.put(cBuffer[i]);
			//std::cout << cBuffer[i];
		}
	}
	//Need to write the end of the buffer
	ofs.write(&cBuffer[ulSizeOfFile - usLengthOfReplacedString],usLengthOfReplacedString);
	//for(int i = usLengthOfReplacedString; i > 0; i--) std::cout << cBuffer[ulSizeOfFile - i];

	//print out how many occurances there were
	std::cout << "\nNumber of Changes: " << unsigned(ulOccuranceCount) << "\n";
	ofs.close();

	delete cBuffer;
	return 0;
}
