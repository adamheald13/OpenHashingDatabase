#ifndef RECORD_H
#define RECORD_H
#include <string>
using namespace std;

class Record {
public:
  Record(string name, string address, long phoneNumber, float charge);

  //getters setters
  string getName();
  string getAddress();
  long getPhoneNumber();
  float getCharge();
  int getAreaCode();

  void changeBalance(float amount);

  //pointers
  Record* nextName;
  Record* nextNumber;
  Record* nextAreaCode;

private:
  //data
  string name;
  string address;
  long phoneNumber;
  float charge;

};

#endif
