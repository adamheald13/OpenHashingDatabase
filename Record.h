#ifndef RECORD_H
#define RECORD_H
#include <string>
using namespace std;

class Record {
public:
  Record(string name, string address, int phoneNumber, float charge);

private:
  //data
  string name;
  string address;
  int phoneNumber;
  float charge;

  //pointers
  Record* nextName;
  Record* nextNumber;
  Record* nextAreaCode;
};

#endif
