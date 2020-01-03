#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <unordered_map>

#include <json/value.h>
#include <boost/algorithm/string.hpp>

#include "utils.hpp" // several useful functions
#include "macros.hpp" // macros used in this file are defined here for better visualization
#include "errors.hpp" // error handling

using namespace std;

const static vector<char> letter_codes[24] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
	'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x'
};

// Cube definition
class Cube {
	public:
		Cube()=default;
		// the following vectors represent the different sticker positions throughout the cube
		// later on they will have a size of 24 integers each
		vector<int> edges;
		vector<int> corners;
};

class Moves : public Cube {
	public:
		Moves()=default;
		// clockwise moves
		void R(Cube); // right layer move 90º clockwise (R)
		void L(Cube); // left layer move 90º clockwise (L)
		void U(Cube); // top layer move 90º clockwise (U)
		void D(Cube); // bottom layer move 90º clockwise (D)
		void F(Cube); // front layer move 90º clockwise (F)
		void B(Cube); // back layer move 90º clocwise (B)

		// counterclockwise moves
		void r(Cube); // right layer move 90º counterclockwise (R')
		void l(Cube); // left layer move 90º counterclockwise (L')
		void u(Cube); // top layer move 90º counterclockwise (U')
		void d(Cube); // bottom layer move 90º counterclockwise (D')
		void f(Cube); // front layer move 90º counterclockwise (F')
		void b(Cube); // back layer move 90º counterclockwise (B')

		// double moves
		void r2(Cube c) { two { R(c); } }
		void l2(Cube c) { two { L(c); } }
		void u2(Cube c) { two { U(c); } }
		void d2(Cube c) { two { D(c); } }
		void f2(Cube c) { two { F(c); } }
		void b2(Cube c) { two { B(c); } }

		/*
			NOTES:
				1. The moves may differ in direction, as they are being treated to be moved
				   clockwise/counterclockwise as if they were in the front layer slot.
				2. Double moves (R2, D2, F2...), this is, 180º moves, are simply represented
				   as double action of the corresponding clockwise move.
		*/
};

class IO : public Cube {
	private:
		int INPUT_TYPE;
	public:
		IO(int _INPUT_TYPE):INPUT_TYPE(_INPUT_TYPE);
		friend void evaluate(IO, Cube); // evaluate the method of input (JSON file/command line input)
		
		// input methods
		void fileInput(const string, Cube);
		void liveInput(Cube);
};

void IO::fileInput(const string filename, Cube c) {
	ifstream scramble_file(filename.c_str(), ifstream::binary);
	scramble_file >> scramble;
	bool letterColors;
	int aux=0;
	vector<string> pieces = {"edges", "corners"}

	if(scramble["input"]=="letters") {
		letterColors = true;
	} else if(scramble["input"]=="numbers") {
		letterColors = false;
	} else {
		rubik_exception::error(EWRONGCOLORINPUT);
	}

	two {
		for(vector<char>::iterator ptr=letter_codes.begin(); ptr<letter_codes.end(); ++ptr) {
			if(letterColors=true){
				if(boost::algorithm::to_lower(scramble[pieces[i]][*ptr])=="white") aux = WHITE;
				else if(boost::algorithm::to_lower(scramble[pieces[i]][*ptr])=="yellow") aux = YELLOW;
				else if(boost::alogrithm::to_lower(scramble[pieces[i]][*ptr])=="green") aux = GREEN;
				else if(boost::algorithm::to_lower(scramble[pieces[i]][*ptr])=="red") aux = RED;
				else if(boost::algorithm::to_lower(scramble[pieces[i]][*ptr])=="blue") aux = BLUE;
				else if(boost::algorithm::to_lower(scramble[pieces[i]][*ptr])=="orange") aux = ORANGE;
				else rubik_exception::error(ENOCOLOR);

				switch(i) {
					case 0:
						c.edges.push_back(aux);
						break;
					case 1:
						c.corners.push_back(aux);
						break;
					default:
						rubik_exception::error(EINDEXOUTOFRANGE);
						break;
				}
			} else {
				if(scramble[pieces[i]][*ptr]>=1 && scramble[pieces[i]][*ptr]<=6) {
					c.edges.push_back(scramble[pieces[i]][*ptr]);
				} else {
					rubik_exception::error(ENOCOLOR);
				}
			}
		}
	}
}

void IO::liveInput(Cube c) {
	vector<string> pieces = {"edges", "corners"}
	vector<string> pieces_sg = {"edge", "corner"}
	string tmp;
	int aux=0;

	two {
		for(vector<char>::iterator ptr=letter_codes.begin(); ptr<letter_codes.end(); ++ptr) {
			cout<<"Introduce color for the "<<boost::algorithm::to_upper(*ptr)<<" "<<pieces_sg[i]<<": ";
			cin>>tmp;
			system("clear");

			tmp = boost::algorithm::to_lower(tmp);

			if(tmp=="white" 		|| tmp=="w" || tmp=="1") aux = WHITE;
			else if(tmp=="yellow" 	|| tmp=="y" || tmp=="2") aux = YELLOW;
			else if(tmp=="green" 	|| tmp=="g" || tmp=="3") aux = GREEN;
			else if(tmp=="red" 		|| tmp=="r" || tmp=="4") aux = RED;
			else if(tmp=="blue" 	|| tmp=="b" || tmp=="5") aux = BLUE;
			else if(tmp=="orange" 	|| tmp=="o" || tmp=="6") aux = ORANGE;
			else rubik_exception::error(ENOCOLOR);

			switch(i) {
				case 0:
					c.edges.push_back(aux);
					break;
				case 1:
					c.corners.push_back(aux);
					break;
				default:
					rubik_exception::error(EINDEXOUTOFRANGE);
					break;
			}
		}
	}
}

int main(int argc, const char* argv[]) {

	return 0;
}

void evaluate(IO obj, Cube c) {
	if(obj.INPUT_TYPE==FINPUT) {
		obj.fileInput("scramble.json", c);
	} else if(obj.INPUT_TYPE==LINPUT) {
		obj.liveInput(c);
	} else {
		rubik_exception::error(EWRONGINPUT);
	}
}