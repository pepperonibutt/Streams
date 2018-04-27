#include "FSerial.h"
#include <fstream>

using namespace std;

OFSerial::OFSerial(std::string fileName) {
  outFile.open(fileName);

  if (!outFile.is_open())
    failed = true;
}

OFSerial::~OFSerial() { outFile.close(); }

OFSerial &OFSerial::operator<<(const bool &input) {
  if (!failed) {

    serial.put(input);
    outFile << serial;
    bool temp;
    serial.get(temp);
  }

  return *this;
}

OFSerial &OFSerial::operator<<(const int &input) {
  if (!failed) {
    serial.put(input);
    outFile << serial;
    int temp;
    serial.get(temp);
  }
  return *this;
}

OFSerial &OFSerial::operator<<(const short &input) {
  if (!failed) {
    serial.put(input);
    outFile << serial;
    short temp;
    serial.get(temp);
  }
  return *this;
}

OFSerial &OFSerial::operator<<(const long &input) {
  if (!failed) {
    serial.put(input);
    outFile << serial;
    long temp;
    serial.get(temp);
  }
  return *this;
}

OFSerial &OFSerial::operator<<(const char &input) {
  if (!failed) {
    serial.put(input);
    outFile << serial;
    char temp;
    serial.get(temp);
  }
  return *this;
}

/*
OFSerial &OFSerial::operator<<(std::string &) {
    serial.put(input);
    outFile << serial;
    bool temp;
    serial.get(temp);
    return *this;
}
*/

bool OFSerial::fail() const { return failed; }

OFSerial::operator bool() const { return !fail(); }
