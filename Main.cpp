#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

void decode(string, map<string, string>&); // prints out the decoded message; Pass in a coded word and the appropriate map

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
	decode(" ___ __ . __. ._", decodemap);
	decode("     _._.     ._ _    ", decodemap);
	decode(" .. ...", decodemap);
	decode(" .... ._ ._. _... .. _. __. . ._.", decodemap);
	decode(" ___ .._.", decodemap);
	decode("_.. . ... _ ._. .._ _._. _ .. ___ _. ", decodemap);
	decode("", decodemap);				// Decode will respond improperly if non-existent codes are passed. (blank codes are fine)
	system("pause"); 
	return;
}

void decode(string code, map<string, string>& decode_map)
{
	code += " "; // Remedy for bug: function ignores the last element of the string. This goes around that (instead of actually fixing it).
	string message;
	string character;
	int index = 0;
	while (index < code.size()){
		if (code[index] == '.' || code[index] == '_' || code[index] == ' '){
			if (code[index] == '.' || code[index] == '_')  // If code isn't a space, save it.
				character += code[index];
			else if (code[index] == ' ' && character.size() < 1){  // Special Case: 
				index++;
				continue; // Only decode the character data if data exists. 
			}
			else if (index == code.size() && character.size() > 0){	// Special Case: Ending of string may not terminate with space.
				message += decode_map[character];
				character.clear();
			}
			else {						// If code is space, decode character data into message, then clear character data
				message += decode_map[character];
				character.clear();
			}
		}
		else {					// Something other than ' ' '.' '_' detected. Run away.
			cout << "Invalid character detected\n";
			return;
		}
		index++;	// keep index updated.
	}
	if (message.size() > 0)
		cout << "message: " << message << "\n";
	else
		cout << "no message found\n";
	return;
}