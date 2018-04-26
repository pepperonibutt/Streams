#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

int length(int i) {
  int bitLength = 1;
  if (i > 0) {
    while (i > 0) {
      i >>= 1;
      bitLength++;
    }
  }
  if (i < 0) {
    i = ~i;
    while (i) {
      i >>= 1;
      bitLength++;
    }
  }
  return bitLength;
}

long lengthLong(long i) {
  int bitLength = 1;
  if (i > 0) {
    while (i > 0) {
      i >>= 1;
      bitLength++;
    }
  }
  if (i < 0) {
    i = ~i;
    while (i) {
      i >>= 1;
      bitLength++;
    }
  }
  return bitLength;
}
unsigned int unsignedLength(unsigned int i) {
  int a = 0;
  while (i > 0) {
    i >>= 1;
    a++;
  }
  return a;
}

unsigned long unsignedLengthLong(unsigned long i) {
  int a = 0;
  while (i > 0) {
    i >>= 1;
    a++;
  }
  return a;
}

void cereal(istream &iss, ostream &oss) {
  int hexVal;
  while (iss >> hexVal) {
    oss << char(hexVal);
  }
}

void vnumshort(ostream &out, short i) {
  int extraBytes;
  int len;
  int b;
  int firstByte;
  len = length(i);
  extraBytes = (len + 3) / 8;
  b = extraBytes;
  b <<= 4;
  firstByte = i >> extraBytes * 8 & 0xF;
  firstByte = b | firstByte;
  out << setw(2) << setfill('0') << (firstByte) << (extraBytes ? ' ' : '\n');
  for (int j = 0; j < extraBytes; j++) {
    out << setw(2) << setfill('0') << ((i >> (extraBytes - j - 1) * 8) & 0xFF);
    if (j == extraBytes - 1)
      out << '\n';
    else
      out << ' ';
  }
}

void vnumint(ostream &out, int i) {
  int extraBytes;
  int len;
  int b;
  int firstByte;
  len = length(i);
  extraBytes = (len + 3) / 8;
  b = extraBytes;
  b <<= 4;
  firstByte = i >> extraBytes * 8 & 0xF;
  firstByte = b | firstByte;
  out << setw(2) << setfill('0') << (firstByte) << (extraBytes ? ' ' : '\n');
  for (int j = 0; j < extraBytes; j++) {
    out << setw(2) << setfill('0') << ((i >> (extraBytes - j - 1) * 8) & 0xFF);
    if (j == extraBytes - 1)
      out << '\n';
    else
      out << ' ';
  }
}

void vnumlong(ostream &out, long i) {
  long extraBytes;
  long len;
  long b;
  long firstByte;
  len = lengthLong(i);
  extraBytes = (len + 3) / 8;
  b = extraBytes;
  b <<= 4;
  firstByte = i >> extraBytes * 8 & 0xF;
  firstByte = b | firstByte;
  out << setw(2) << setfill('0') << (firstByte) << (extraBytes ? ' ' : '\n');
  for (int j = 0; j < extraBytes; j++) {
    out << setw(2) << setfill('0') << ((i >> (extraBytes - j - 1) * 8) & 0xFF);
    if (j == extraBytes - 1)
      out << '\n';
    else
      out << ' ';
  }
}

void serialize(bool boolean, ostream &out) {
  if (boolean)
    out << 't';
  else
    out << 'f';
}

string unserialize(istream &in, bool &output) {
  char character;
  in.get(character);
  if (character != 'f' && character != 't') {
    in.unget();
    throw string("The input stream given does not correspond to a boolean.");
  }
  output = character == 't' ? true : false;

  string temp;

  getline(in, temp);

  return temp;
}

void serialize(short input, ostream &out) {
  ostringstream oss;
  istringstream iss;
  vnumshort(oss, input);
  iss.str(oss.str());
  out << 's';
  cereal(iss, out);
}

void serialize(int input, ostream &out) {
  ostringstream oss;
  istringstream iss;
  vnumint(oss, input);
  iss.str(oss.str());
  out << 'i';
  cereal(iss, out);
}

void serialize(long input, ostream &out) {
  ostringstream oss;
  istringstream iss;
  vnumlong(oss, input);
  iss.str(oss.str());
  out << 'l';
  cereal(iss, out);
}

void serialize(char input, ostream &out) {
  out << 'c';
  out.put(input);
  // out << 'c' << input;
}

void serialize(const string &input, ostream &out) {
  out << 'S';
  ostringstream oss;
  istringstream iss;
  int stringLength = input.length();
  vnumint(oss, stringLength);
  iss.str(oss.str());
  cereal(iss, out);
  out << input;
}

string unserialize(istream &iss, short &output) {
  char character;
  char hexVal;
  iss.get(character);
  output = 0;

  if (character != 's') {
    ostringstream errorMsg;
    errorMsg << "The input stream has the wrong tag! The tag we found was ";
    errorMsg << character;
    errorMsg << '.';
    iss.unget();
    throw string(errorMsg.str());
  }

  iss >> hex >> hexVal;
  unsigned int lenVnum = hexVal & 0xF0;
  lenVnum >>= 4; // now i have the length of the vnum in lenVnum
  int shift = lenVnum * 8;
  unsigned int sign = hexVal & 0x08;
  hexVal = hexVal & 0x0F;
  if (shift > 0) {
    hexVal <<= shift;
    shift -= 8;
  }
  output += hexVal;

  if (sign == 0x08) { // negative case
    if (shift > 0) {
      hexVal <<= shift;
      shift -= 8;
    }
    for (unsigned int i = 0; i < lenVnum; i++) {
      iss >> hexVal;

      if (shift > 0) {
        hexVal <<= shift;
        shift -= 8;
      }
      output += hexVal;
    }
    unsigned int bitManip = output;

    unsigned int lengthOfVal = unsignedLength(bitManip);

    lengthOfVal = 32 - lengthOfVal;

    bitManip = ~bitManip;

    bitManip += 1;

    bitManip <<= lengthOfVal;
    bitManip >>= lengthOfVal;

    ostringstream out;
    out << '-' << bitManip;

    istringstream in;
    in.str(out.str());

    in >> output;
  }

  if (sign == 0x00) {
    for (unsigned int i = 0; i < lenVnum; i++) {
      iss >> hexVal;
      hexVal <<= shift;
      shift -= 8;
      output += hexVal;
    }
  }

  string temp = "";
  char c;

  while (iss.get(c)) {
    temp += c;
  }

  return temp;
}

string unserialize(istream &iss, int &output) {
  char character;
  char hexVal;
  iss.get(character);
  output = 0;

  if (character != 'i') {
    ostringstream errorMsg;
    errorMsg << "The input stream has the wrong tag! The tag we found was ";
    errorMsg << character;
    errorMsg << '.';
    iss.unget();
    throw string(errorMsg.str());
  }

  iss.get(hexVal);

  unsigned int lenVnum = hexVal & 0xF0;
  lenVnum >>= 4; // now i have the length of the vnum in lenVnum
  int shift = lenVnum * 8;
  unsigned int sign = hexVal & 0x08;
  hexVal = hexVal & 0x0F;

  unsigned int unsignedhexVal = int(hexVal);
  if (shift > 0) {
    unsignedhexVal <<= shift;
    shift -= 8;
  }
  output += unsignedhexVal;
  if (sign == 0x08) { // negative case
    for (unsigned int i = 0; i < lenVnum; i++) {
      iss.get(hexVal);
      if (shift > 0) {
        hexVal <<= shift;
        shift -= 8;
      }
      output += hexVal;
    }
    unsigned int bitManip = output;
    unsigned int lengthOfVal = unsignedLength(bitManip);
    lengthOfVal = 32 - lengthOfVal;
    bitManip = ~bitManip;
    bitManip += 1;
    bitManip <<= lengthOfVal;
    bitManip >>= lengthOfVal;
    ostringstream out;
    out << '-' << bitManip;
    istringstream in;
    in.str(out.str());
    in >> output;
  }

  if (sign == 0x00) { // positive case
    for (unsigned int i = 0; i < lenVnum; i++) {
      unsignedhexVal = 0;
      iss.get(hexVal);
      unsignedhexVal = int(hexVal);
      unsignedhexVal <<= 24;
      unsignedhexVal >>= 24;
      unsignedhexVal <<= shift;
      if (shift > 0) {
        shift -= 8;
      }
      output += unsignedhexVal;
    }
  }

  string temp = "";
  char c;

  while (iss.get(c)) {
    temp += c;
  }

  return temp;
}

string unserialize(istream &iss, long &output) {
  char character;
  char hexVal;
  iss.get(character);
  output = 0;

  if (character != 'l') {
    ostringstream errorMsg;
    errorMsg << "The input stream has the wrong tag! The tag we found was ";
    errorMsg << character;
    errorMsg << '.';
    iss.unget();
    throw string(errorMsg.str());
  }

  iss.get(hexVal);
  unsigned int lenVnum = hexVal & 0xF0;
  lenVnum >>= 4; // now i have the length of the vnum in lenVnum
  int shift = lenVnum * 8;
  unsigned int sign = hexVal & 0x08;
  hexVal = hexVal & 0x0F;
  unsigned long unsignedhexVal = long(hexVal);
  if (shift > 0) {
    unsignedhexVal <<= shift;
    shift -= 8;
  }
  output += unsignedhexVal;
  if (sign == 0x08) { // negative case
    for (unsigned int i = 0; i < lenVnum; i++) {
      iss.get(hexVal);
      if (shift > 0) {
        hexVal <<= shift;
        shift -= 8;
      }
      output += hexVal;
    }
    unsigned long bitManip = output;
    unsigned long lengthOfVal = unsignedLengthLong(bitManip);
    lengthOfVal = 64 - lengthOfVal;
    bitManip = ~bitManip;
    bitManip += 1;
    bitManip <<= lengthOfVal;
    bitManip >>= lengthOfVal;
    ostringstream out;
    out << '-' << bitManip;
    istringstream in;
    in.str(out.str());
    in >> output;
  }

  if (sign == 0x00) { // positive case
    for (unsigned int i = 0; i < lenVnum; i++) {
      unsignedhexVal = 0;
      iss.get(hexVal);
      unsignedhexVal = int(hexVal);
      unsignedhexVal <<= 56;
      unsignedhexVal >>= 56;
      unsignedhexVal <<= shift;
      if (shift > 0) {
        shift -= 8;
      }
      output += unsignedhexVal;
    }
  }

  string temp = "";
  char c;

  while (iss.get(c)) {
    temp += c;
  }

  return temp;
}

string unserialize(istream &iss, char &output) {
  char character;
  iss.get(character);
  if (character != 'c') {
    ostringstream errorMsg;
    errorMsg << "The input stream has the wrong tag! The tag we found was ";
    errorMsg << character;
    errorMsg << '.';
    iss.unget();
    throw string(errorMsg.str());
  }
  iss.get(output);

  string temp = "";
  char c;

  while (iss.get(c)) {
    temp += c;
  }

  return temp;
}

string unserialize(istream &in, string &output) {
  int stringLength = 0;
  ostringstream oss;
  istringstream iss;
  char hexVal;
  unsigned int lenVnum, unsignedhexVal;
  in.get(hexVal);

  if (hexVal != 'S') {
    ;
    ostringstream errorMsg;
    errorMsg << "The input stream has the wrong tag! The tag we found was ";
    errorMsg << hexVal;
    errorMsg << '.';
    in.unget();
    throw string(errorMsg.str());
  }

  in.get(hexVal);
  lenVnum = hexVal & 0xF0;
  lenVnum >>= 4;
  int shift = lenVnum * 8;
  hexVal = hexVal & 0x0F;
  stringLength += hexVal;

  for (unsigned int i = 0; i < lenVnum; ++i) {
    in.get(hexVal);
    unsignedhexVal = int(hexVal);
    unsignedhexVal <<= 24;
    unsignedhexVal >>= 24;
    unsignedhexVal <<= shift;
    if (shift > 0) {
      shift -= 8;
    }
    stringLength += unsignedhexVal;
  }
  // correct string length so everything up to this point is correct, but for
  // some reason, the string has hex 03/03/03 in it instead of xyz
  for (int i = 0; i < stringLength; i++) {
    iss.get(hexVal);
    // oss << hexVal;
    output += hexVal;
  }
  // output = oss.str();

  string temp = "";
  char c;

  while (iss.get(c)) {
    temp += c;
  }

  return temp;
}
