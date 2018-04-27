#include "FSerial.h"
#include <fstream>
#include <string>
using namespace std;

IFSerial::IFSerial(string s) {
  inFile.open(s);
  if (!inFile.is_open())
    failed = true;
  else {
    string temp = "";
    char c;
    while (inFile.get(c)) {
         temp += c;
    }
    serial.str(temp);
  }
}

IFSerial::~IFSerial() { inFile.close(); }

IFSerial &IFSerial::operator>>(bool &out) {
  try {
    serial.get(out);
  } catch (...) {
    failed = true;
  }
  return *this;
}

IFSerial &IFSerial::operator>>(int &out) {
  try {
    serial.get(out);
  } catch (...) {
    failed = true;
  }
  return *this;
}
IFSerial &IFSerial::operator>>(short &out) {
  try {
    serial.get(out);
  } catch (...) {
    failed = true;
  }

  return *this;
}
IFSerial &IFSerial ::operator>>(long &out) {
  try {
    serial.get(out);
  } catch (...) {
    failed = true;
  }

  return *this;
}
IFSerial &IFSerial::operator>>(char &out) {
  try {
    serial.get(out);
  } catch (...) {
    failed = true;
  }

  return *this;
}
/*
IFSerial &IFSerial::operator>>(std::string &out) {
  try {
    serial.get(out);
  } catch (...) {
    failed = true;
  }

  return *this;
}
*/

bool IFSerial::eof() const { return serial.empty(); }

bool IFSerial::fail() const { return failed; }

IFSerial::operator bool() const { return !eof() || !fail(); }
