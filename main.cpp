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

	//Find the size of both substrings
	while(argv[2][usLengthOfReplacedString] != '\0') usLengthOfReplacedString++;
	while(argv[3][usLengthOfReplacingString] != '\0') usLengthOfReplacingString++;

	//create an input stream
	std::ifstream ifs(argv[1],std::ifstream::in);
	
	//find the size of the file
	ifs.seekg(0,ifs.end);
	ulSizeOfFile = ifs.tellg();
	//return to the beginning of the file
	ifs.seekg(0);

	//Place the file contents within a buffer
	char * cBuffer = new char[ulSizeOfFile];
	ifs.read(cBuffer,ulSizeOfFile);

	//close the input stream
	ifs.close();

	//delete the file
	if (remove(argv[1]) != 0)
	{
		std::cout <<"ERROR: File work error - remove(<File_Name>) != 0\n";
	       	std::cout <<"Most Likely due to not executing with high enough privelege state\n"; 
		return 0; 
	}	
	
	//create an output stream
	std::ofstream ofs(argv[1],std::ofstream::out);

	//This variable helps to find the substring later on
	int j;

	std::cout << "\nStart Parsing\n";

	//In the special case that we are replacing a single character
	if(usLengthOfReplacedString == 1)
	{
		for(int i = 0; i < ulSizeOfFile; i++)
		{
			if(cBuffer[i] == argv[2][0]) 
			{
				ulOccuranceCount++;
				ofs.write(argv[3],usLengthOfReplacingString);
			}
			else ofs.put(cBuffer[i]);
		}
	}
	else
	{
		//Check all possible spots within the buffer for the substring
		for(int i = 0; i < ulSizeOfFile - usLengthOfReplacedString; i++)
		{
			j = 1;
			if(cBuffer[i] == argv[2][0])
			{
				while(j < usLengthOfReplacedString && cBuffer[i+j] == argv[2][j]) j++;		
			}
			if(j == usLengthOfReplacedString)
			{
				ofs.write(argv[3],usLengthOfReplacingString);
				i += usLengthOfReplacedString - 1;
				ulOccuranceCount++;
			}
			else 
			{
				ofs.put(cBuffer[i]);
				
			}
		}
		
		ofs.write(&cBuffer[ulSizeOfFile - usLengthOfReplacedString],usLengthOfReplacedString);
		
	}

	//print out how many occurances there were
	std::cout << "\nNumber of Changes: " << unsigned(ulOccuranceCount) << "\n";
	ofs.close();

	delete cBuffer;
	return 0;
}
