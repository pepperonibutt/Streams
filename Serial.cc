#include <iostream>
#include <sstream>
#include <string>

#include "Serial.h"
using namespace std;

Serial::Serial(){
		iss.str("");
		oss.str("");
	}
Serial::Serial(string s){
		iss.str(s);
		oss.str(s);
	}
Serial::Serial(const Serial & other){
		iss.str(other.iss.str());
		oss.str(other.oss.str());
	}
	Serial & Serial::operator=(const Serial & other){
		iss.str(other.iss.str());
		oss.str(other.oss.str());
		return *this;
	}

	void Serial::put(bool in){
		serialize(in, oss);
		iss.str(oss.str());
	}
	void Serial::put(short in){
		serialize(in, oss);
		iss.str(oss.str());
	}
	void Serial::put(int in){
		serialize(in, oss);
		iss.str(oss.str());
	}
	void Serial::put(char in){
		serialize(in, oss);
		iss.str(oss.str());
	}
	void Serial::put(string in){
		serialize(in, oss);
		iss.str(oss.str());
	}

    void Serial::put(long in) {
        serialize(in, oss);
        iss.str(oss.str());
    }

	void Serial::get(bool &out){
		iss.str(unserialize(iss, out));
		oss.str(iss.str());
        iss.clear();
	}
	void Serial::get(short &out){
		iss.str(unserialize(iss, out));
		oss.str(iss.str());
        iss.clear();
	}
	void Serial::get(int &out){
	    iss.str(unserialize(iss, out));
		oss.str(iss.str());
        iss.clear();
	}
	void Serial::get(long &out){
        iss.str(unserialize(iss, out));
		oss.str(iss.str());
        iss.clear();
	}
	void Serial::get(char &out){
		iss.str(unserialize(iss, out));
		oss.str(iss.str());
		iss.clear();
    }
	void Serial::get(string &out){
		out = "";
    //   iss.str(unserialize(iss, out));
	//	oss.str(iss.str());
    //   iss.clear();
	}

	string Serial::str() const {
		return iss.str();
	}

	void Serial::str(string in){
		iss.str(in);
		oss.str(in);
        //iss.clear();
	}

	int Serial::size() const {
		int size = iss.str().length();
		return size;
	}

	bool Serial::empty() const {
		return (iss.str().length() == 0);
	}

ostream &operator<<(ostream &out, const Serial &in){
		out << in.iss.str();
		return out;
}

Serial &Serial::operator+=(const bool &data){
	//ostringstream temp;
	//temp.str("");
	//serialize(data, oss);
	put(data);
	//string s = iss.str() + temp.str();
	//iss.str(s);
	//oss.str(s);
	return *this;
}

Serial &Serial::operator+=(const int &data){
	put(data);
	return *this;
}

Serial &Serial::operator+=(const short &data){
	put(data);
	return *this;
}

Serial &Serial::operator+=(const long &data){
	put(data);
	return *this;
}

Serial &Serial::operator+=(const char &data){
	put(data);
	return *this;
}

Serial &Serial::operator+=(const Serial &data){
	string s = iss.str() + data.str();
	iss.str(s);
	return *this;
}

Serial Serial::operator+(const bool &data) const{
	Serial temp;
	temp.str(iss.str());
	return temp+=data;
}

Serial Serial::operator+(const int &data) const{
	Serial temp;
	temp.str(iss.str());
	return temp+=data;
}

Serial Serial::operator+(const short &data) const{
	Serial temp;
	temp.str(iss.str());
	return temp+=data;
}

Serial Serial::operator+(const long &data) const{
	Serial temp;
	temp.str(iss.str());
	return temp+=data;
}

Serial Serial::operator+(const char &data) const{
	Serial temp;
	temp.str(iss.str());
	return temp+=data;
}

Serial Serial::operator+(const Serial &data) const{
	Serial temp;
	temp.str(iss.str());
	return temp+=data;
}

Serial operator+(const bool data, const Serial &cereal){
	Serial temp;
	temp+=data;
	string s = temp.str() + cereal.str();
	temp.str(s);
	return temp;
}

Serial operator+(const int data, const Serial &cereal){
	Serial temp;
	temp+=data;
	string s = temp.str() + cereal.str();
	temp.str(s);
	return temp;
}

Serial operator+(const short data, const Serial &cereal){
	Serial temp;
	temp+=data;
	string s = temp.str() + cereal.str();
	temp.str(s);
	return temp;
}

Serial operator+(const long data, const Serial &cereal){
	Serial temp;
	temp+=data;
	string s = temp.str() + cereal.str();
	temp.str(s);
	return temp;
}

Serial operator+(const char data, const Serial &cereal){
	Serial temp;
	temp+=data;
	string s = temp.str() + cereal.str();
	temp.str(s);
	return temp;
}

void operator<<=(char &data,  Serial &cereal){
	cereal.get(data);
}

void operator<<=(bool &data,  Serial &cereal){
	cereal.get(data);
}

void operator<<=(short &data,  Serial &cereal){
	cereal.get(data);
}

void operator<<=(int &data,  Serial &cereal){
	cereal.get(data);
}

void operator<<=(long &data,  Serial &cereal){
	cereal.get(data);
}

bool Serial::operator==(const Serial &rhs)const{
	return (iss.str() == rhs.str());
}

bool Serial::operator!=(const Serial &rhs)const{
	return (iss.str() != rhs.str());
}


Serial::~Serial() {
    
}
