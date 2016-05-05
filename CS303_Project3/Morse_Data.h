#ifndef MORSE_DATA_H
#define MORSE_DATA_H
#include <string>
using namespace std;

class Morse_Data{
public:
	char letter;
	string code;

	Morse_Data(char l, string c){
		letter = l;
		code = c;
	}
	
	friend bool operator<(const Morse_Data& m1, const Morse_Data& m2){
		return m1.code < m2.code;
	}

	friend ostream& operator<<(ostream& os, const Morse_Data& m){
		os << m.letter << m.code;
		return os;
	}

};



#endif