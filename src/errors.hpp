#ifndef RUBIK_ERRORS_HPP
#define RUBIK_ERRORS_HPP

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

#include "utils.hpp"
#include "macros.hpp"

using namespace std;

namespace rubik_exception {
	void error(int ERROR_CODE, string msg) {
		switch(ERROR_CODE) {
			case ECRASH:
				cout<<"ERROR ("<<msg<<"), ECRASH: unexpected program crash.\nTerminating execution."<<endl;
				exit(0);
				break;
			case EWRONGINPUT:
				cout<<"ERROR ("<<msg<<"), EWRONGINPUT: unkown scramble input method. Only possibilities are FINPUT (file input) and LINPUT (line input).\nTerminating execution."<<endl;
				exit(0);
				break;
			case EWRONGCOLORINPUT:
				cout<<"ERROR ("<<msg<<"), EWRONGCOLORINPUT: unknown color input method. Only possibilities are 'letters' and 'numbers'.\nTerminating execution."<<endl;
				exit(0);
				break;
			case ENOCOLOR:
				cout<<"ERROR ("<<msg<<"), ENOCOLOR: not a valid color [white/yellow/green/red/blue/orange].\nTerminating execution."<<endl;
				exit(0);
				break;
			case EINDEXOUTOFRANGE:
				cout<<"ERROR ("<<msg<<"), EINDEXOUTOFRANGE: index out of range in loop.\nTerminating execution."<<endl;
				exit(0);
				break;
			default:
				cout<<"ERROR (given index "<<ERROR_CODE<<"), ENOERROR: no error found associated to that index.\nTerminating execution."<<endl;
				exit(0);
				break;
		}
	}
}

#endif