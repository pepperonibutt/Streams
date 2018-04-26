#ifndef _F_SERIAL_H_
#define _F_SERIAL_H_

#include "Serial.h"
#include <fstream>
#include <string>

class IFSerial {
  Serial serial;
  std::ifstream inFile;
  bool failed;

public:
  IFSerial(std::string);
  ~IFSerial();

  IFSerial &operator>>(bool &);
  IFSerial &operator>>(int &);
  IFSerial &operator>>(short &);
  IFSerial &operator>>(long &);
  IFSerial &operator>>(char &);
  IFSerial &operator>>(std::string &);

  bool eof() const;
  bool fail() const;

  operator bool() const;
};

class OFSerial {
  Serial serial;
  std::ofstream outFile;
  bool failed;

public:
  OFSerial(std::string);
  ~OFSerial();

  OFSerial &operator<<(const bool &);
  OFSerial &operator<<(const int &);
  OFSerial &operator<<(const short &);
  OFSerial &operator<<(const long &);
  OFSerial &operator<<(const char &);
  // OFSerial &operator<<(const std::string &);

  bool fail() const;

  operator bool() const;
};

#endif
