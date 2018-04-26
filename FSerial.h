#ifndef _F_SERIAL_H_
#define _F_SERIAL_H_

#include <string>
#include <fstream>
#include "Serial.h"

class IFSerial {
    Serial serial;
    std::ifstream inFile;

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

public:
    OFSerial(std::string);
    ~OFSerial();

    OFSerial &operator<<(bool &);
    OFSerial &operator<<(int &);
    OFSerial &operator<<(short &);
    OFSerial &operator<<(long &);
    OFSerial &operator<<(char &);
    OFSerial &operator<<(std::string &);
    
    bool fail() const;

    operator bool() const;
};

#endif
