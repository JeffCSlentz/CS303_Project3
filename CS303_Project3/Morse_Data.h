#ifndef MORSE_DATA_H
#define MORSE_DATA_H
#include <string>
using namespace std;

class Morse_Data{
public:
	char letter;
	string code;
	int index;

	Morse_Data(char l, string c){
		letter = l;
		code = c;
		int i = 0;
		for (string::iterator itr = c.begin(); itr != c.end(); itr++){
			if (*itr == '.'){
				index = (2 * i) + 1;
				i = index;
			}
			else{
				index = (2 * i) + 2;
				i = index;
			}
		}
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