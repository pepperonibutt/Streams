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

void IFSerial::print() {
  cout << serial.empty() << endl;
  cout << serial << endl;
}

IFSerial::~IFSerial() { inFile.close(); }

IFSerial &IFSerial::operator>>(bool &out) {
  if (serial.empty()) {
    endoffile = true;
    failed = true;
  } else {
    try {
      serial.get(out);
    } catch (...) {
      failed = true;
    }
  }
  return *this;
}

IFSerial &IFSerial::operator>>(int &out) {
  if (serial.empty()) {
    endoffile = true;
    failed = true;
  } else {
    try {
      serial.get(out);
    } catch (...) {
      failed = true;
    }
  }
  return *this;
}
IFSerial &IFSerial::operator>>(short &out) {
  if (serial.empty()) {
    endoffile = true;
    failed = true;
  } else {
    try {
      serial.get(out);
    } catch (...) {
      failed = true;
    }
  }
  return *this;
}
IFSerial &IFSerial ::operator>>(long &out) {
  if (serial.empty()) {
    endoffile = true;
    failed = true;
  } else {
    try {
      serial.get(out);
    } catch (...) {
      failed = true;
    }
  }
  return *this;
}
IFSerial &IFSerial::operator>>(char &out) {
  if (serial.empty()) {
    endoffile = true;
    failed = true;
  } else {
    try {
      serial.get(out);
    } catch (...) {
      failed = true;
    }
  }
  return *this;
}
/*IFSerial &IFSerial::operator>>(std::string &out) {
  try {
    serial.get(out);
  } catch (...) {
    failed = true;
  }

  return *this;
}
*/
bool IFSerial::eof() const { return endoffile; }

bool IFSerial::fail() const { return failed; }

IFSerial::operator bool() const { return !eof() && !fail(); }
