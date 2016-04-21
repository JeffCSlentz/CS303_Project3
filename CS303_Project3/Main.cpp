#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

void main(){
	ifstream fin("mores.txt");			//Open the input file.
	
	//Variables.
	string buffer;
	string character;
	string code;

	map<string, string> encodemap;		//This map is for encoding a message.
	map<string, string> decodemap;		//This map is for decoding.

	while (fin >> buffer){				//Read in a string from the file (separated by space or newline).

		character = buffer[0];			//The character is the first index.
		code = string(buffer, 1);		//The code is the second index to the end of buffer.

		encodemap[character] = code;	//Write into encodemap: (key = char, value = code);
		decodemap[code] = character;	//Write into decodemap: (key = code, value = char);
	}

	fin.close();						//Close the file.

	system("pause"); 
	return;
}