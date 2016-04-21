#include "Record.h"

Record::Record(string name, string address, long phoneNumber, float charge) {
  this->name = name;
  this->address = address;
  this->phoneNumber = phoneNumber;
  this->charge = charge;

  nextName = 0;
  nextNumber = 0;
  nextAreaCode = 0;
}

string Record::getName() {
  return this->name;
}

string Record::getAddress() {
  return this->address;
}

long Record::getPhoneNumber() {
  return this->phoneNumber;
}

float Record::getCharge() {
  return this->charge;
}

int Record::getAreaCode() {
  return this->phoneNumber / 10000000;
}

void Record::changeBalance(float amount) {
  this->charge = this->charge + amount;
}
