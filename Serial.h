#ifndef _SERIAL_H
#define _SERIAL_H

#include <iostream>
#include <string>
#include <sstream>

class Serial {
    private:
        std::istringstream iss;
        std::ostringstream oss;
        
    public:
        Serial();
        explicit Serial(std::string );
        Serial(const Serial &);
        Serial &operator=(const Serial &);
        ~Serial();

        std::string str() const;
        void str(std::string);
        int size() const;
        bool empty() const;

        void put(bool);
        void put(short);
        void put(int);
        void put(long);
        void put(char);
        void put(std::string);

        void get(bool &);
        void get(short &);
        void get(int &);
        void get(long &);
        void get(char &);
        void get(std::string &);

        friend std::ostream &operator<<(std::ostream &, const Serial &);

         Serial &operator+=(const bool &);
         Serial &operator+=(const int &);
         Serial &operator+=(const short &);
         Serial &operator+=(const long &);
         Serial &operator+=(const char &);
         Serial &operator+=(const Serial &);

         Serial operator+(const bool &data)const;
         Serial operator+(const int &data)const;
         Serial operator+(const short &data)const;
         Serial operator+(const long &data)const;
         Serial operator+(const char &data)const;
         Serial operator+(const Serial &data)const;

         bool operator==(const Serial &rhs)const;
         bool operator!=(const Serial &rhs)const;

         friend Serial operator+(const char data, const Serial &cereal);
         friend Serial operator+(const int data, const Serial &cereal);
         friend Serial operator+(const short data, const Serial &cereal);
         friend Serial operator+(const long data, const Serial &cereal);
         friend Serial operator+(const char data, const Serial &cereal);

         friend void operator<<=(char &data,  Serial &cereal);
         friend void operator<<=(bool &data,  Serial &cereal);
         friend void operator<<=(int &data,  Serial &cereal);
         friend void operator<<=(short &data,  Serial &cereal);
         friend void operator<<=(long &data,  Serial &cereal);

};

void serialize(bool, std::ostream &);
void serialize(short, std::ostream &);
void serialize(int, std::ostream &);
void serialize(long, std::ostream &);
void serialize(char, std::ostream &);
void serialize(const std::string &, std::ostream &);

std::string unserialize(std::istream &, bool &);
std::string unserialize(std::istream &, short &);
std::string unserialize(std::istream &, int &);
std::string unserialize(std::istream &, long &);
std::string unserialize(std::istream &, char &);
std::string unserialize(std::istream &, std::string &);

 

#endif
