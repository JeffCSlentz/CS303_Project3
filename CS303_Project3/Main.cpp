#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Binary_Search_Tree.h"
#include "Morse_Data.h"

using namespace std;

void decode(string, map<string, string>&); // prints out the decoded message; Pass in a coded word and the appropriate map

//Added 4-28 by Jeff. Makes a Binary tree that represents the data.
Binary_Tree<Morse_Data> buildDecodeTree();
void insertMorseNode(const Morse_Data& MD, vector<char>& vec, int i, BTNode<Morse_Data>* currentRoot);

void main(){

	//Build the binary tree and save it as decodeTree.
	Binary_Tree<Morse_Data> decodeTree = buildDecodeTree();

	string buffer;
	string character;
	string code;

	map<string, string> encodemap;		//This map is for encoding a message.
	map<string, string> decodemap;		//This map is for decoding.

	ifstream fin2("mores.txt");
	while (fin2 >> buffer){				//Read in a string from the file (separated by space or newline).

		character = buffer[0];			//The character is the first index.
		code = string(buffer, 1);		//The code is the second index to the end of buffer.

		encodemap[character] = code;	//Write into encodemap: (key = char, value = code);
		decodemap[code] = character;	//Write into decodemap: (key = code, value = char);
	}
	
	fin2.close();						//Close the file.


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
		cout << "Message: " << message << "\n";
	else
		cout << "No message found\n";
	return;
}


//Makes a binary tree, assuming there's a file called 'mores.txt' filled with appropriately formatted text
Binary_Tree<Morse_Data> buildDecodeTree(){
	//Open the input file.
	ifstream fin("mores.txt");			

	//Create the decodeTree with the main root. (Has dummy data in it)
	Binary_Tree<Morse_Data> decodeTree = Binary_Tree<Morse_Data>();
	BTNode<Morse_Data> theRoot = BTNode<Morse_Data>(Morse_Data('0', "0"));
	decodeTree.setRoot(&theRoot);

	//String to hold text from the file.
	string temp_Buffer;

	//While there is text left to read in the file.
	while (fin >> temp_Buffer){
		
		//Temporary vector to make life easier.
		vector<char> vec;

		//Create a morse data with letter being the first index of temp_buffer and the code being the rest of the indeces.
		Morse_Data current_MD = Morse_Data(temp_Buffer[0], string(temp_Buffer, 1)); //Initialize the data.

		//Iterate through the code (.__._), putting each character into its own vector index.
		string code = string(temp_Buffer, 1);
		for (string::iterator itr = code.begin(); itr != code.end(); itr++){
			vec.push_back(*itr);
		}

		//Initialize a counter.
		int i = 0;
		//Call this monster
		insertMorseNode(current_MD, vec, i, &theRoot);
	}

	//Close your files yo
	fin.close();
	
	return decodeTree;
}

//Recursive function that reads a vector of chars to determine where to make a new node with it's Morse_data.
//It will create dummy nodes along it's path.
void insertMorseNode(const Morse_Data& MD, vector<char>& vec, int i, BTNode<Morse_Data>* currentRoot){

	if (i == vec.size()-1){						//Check if we're at the end of the code (._._) and if we need to make or modify the node now.

		if (vec[i] == '.'){						//Make or modify the left node.

			if (currentRoot->left == NULL){		//Make a left node.
				currentRoot->left = new BTNode < Morse_Data>(MD);
			}
			else{
				currentRoot->left->data = MD;	//Modify the left node.
			}

		}
		else{									//Make or modify the right node.

			if (currentRoot->right == NULL){	//Make the right node.
				currentRoot->right = new BTNode < Morse_Data>(MD);
			}
			else{								//Modify the right node.
				currentRoot->right->data = MD;
			}
		}
		//We've changed the node, jump back through the traversal portal.
		return;
	}

	else{										//We still need to traverse the tree.

		//Check the current character.
		if (vec[i] == '.'){						//Go left.
			if (currentRoot->left == NULL){		//If there's no left node, make a dummy node.
				currentRoot->left = new BTNode < Morse_Data>(Morse_Data('0', "0"));
			}
			i++;
			insertMorseNode(MD, vec, i, currentRoot->left);		//Recursively call this function

			//Once we're finally back from the function call above, head back out.
			return;
		}

		else{									//Go Right.
			if (currentRoot->right == NULL){	//If there's no left node, make a dummy node.
				Morse_Data dummyData = Morse_Data('0', "0");
				currentRoot->right = new BTNode < Morse_Data>(Morse_Data('0', "0"));
			}
			i++;
			insertMorseNode(MD, vec, i, currentRoot->right);	//Recursively call this function


			//Once we're finally back from the function call above, head back out.
			return;
		}
	}
}