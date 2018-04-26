#include "FSerial.h"
#include <fstream>
#include <string>
using namespace std;

IFSerial::IFSerial(string s){
	inFile.open(s);
	if (!inFile.is_open())
		failed=true;
	string temp="";
	char c;
	while (inFile.get(c)){
		temp+=c;
	}
	serial(temp);
}

IFSerial&::IFSerial operator>>(bool &out){
	try{
		serial.get(out);
	} catch(...){
		failed=true;
	}
	
}
IFSerial&::IFSerial operator>>(int &out){
	try{
		serial.get(out);
	} catch(...){
		failed=true;
	}
}
IFSerial&::IFSerial operator>>(short &out){
	try{
		serial.get(out);
	} catch(...){
		failed=true;
	}
}
IFSerial&::IFSerial operator>>(long &out){
	try{
		serial.get(out);
	} catch(...){
		failed=true;
	}
}
IFSerial&::IFSerial operator>>(char &out){
	try{
		serial.get(out);
	} catch(...){
		failed=true;
	}
}
IFSerial&::IFSerial operator>>(std::string &out){
	try{
		serial.get(out);
	} catch(...){
		failed=true;
	}
}

bool eof() const{
return serial.empty();
}
bool fail() const{
	return failed;
}

operator bool() const{
	return !eof()&&!fail();
}