#include "Database.h"
#include <iostream>
#include <string.h>
using namespace std;

Database::Database() {
  for(int i = 0; i < 113; i++) {
    if(i < 47)
      names[i] = 0;
    if(i < 53)
      numbers[i] = 0;
    areaCodes[i] = 0;
  }
}

void Database::insert(Record* record, bool isInit) {
  insertRecordByName(record);
  insertRecordByNumber(record);
  insertRecordByAreaCode(record);
  if(!isInit)
    cout << record->getName() << " was inserted into the database." << endl;
}

void Database::insertRecordByName(Record* record) {
  int mod = (record->getName()[1] + record->getName()[6] + record->getName()[12]) % 47;

  Record* temp;

  if(names[mod] == 0)
    names[mod] = record;
  else {
    temp = names[mod];
    while(temp->nextName != 0)
      temp = temp->nextName;
    temp->nextName = record;
  }
}

void Database::insertRecordByNumber(Record* record) {
  long mod = record->getPhoneNumber();
  mod = mod % 10000;
  mod = mod % 53;

  Record* temp;

  if(numbers[mod] == 0)
    numbers[mod] = record;
  else {
    temp = numbers[mod];
    while(temp->nextNumber != 0)
      temp = temp->nextNumber;
    temp->nextNumber = record;
  }
}

void Database::insertRecordByAreaCode(Record* record) {
  long mod = record->getPhoneNumber();
  mod = mod / 10000000;
  mod = mod * (mod * 3) % 113;

  Record* temp;

  if(areaCodes[mod] == 0)
    areaCodes[mod] = record;
  else {
    temp = areaCodes[mod];
    while(temp->nextAreaCode != 0)
      temp = temp->nextAreaCode;
    temp->nextAreaCode = record;
  }
}

void Database::deleteRecord(long number) {
  Record* temp = getRecord(number);
  removeRecord(temp->getPhoneNumber());
  removeRecord(temp->getName());
  removeRecord(temp->getPhoneNumber(), temp->getName());
  cout << temp->getName() << " was removed from the database." << endl
       << "Final bill: " << temp->getCharge() << endl;
}

void Database::deleteRecord(string name) {
  Record* temp = getRecord(name);
  removeRecord(temp->getPhoneNumber());
  removeRecord(temp->getName());
  removeRecord(temp->getPhoneNumber(), temp->getName());
  cout << temp->getName() << " was removed from the database." << endl
       << "Final bill: " << temp->getCharge() << endl;
}

void Database::removeRecord(long number) {
  long mod = number;
  mod = mod % 10000;
  mod = mod % 53;

  if(numbers[mod] == 0)
    cout << "No record with that phone number exists." << endl;
  else {
    Record* current = numbers[mod];
    Record* previous = 0;

    if(numbers[mod]->getPhoneNumber() == number)
      numbers[mod] = current->nextNumber;
    else {
      while(current->getPhoneNumber() != number) {
        previous = current;
        current = current->nextNumber;
      }
      previous->nextNumber = current->nextNumber;
    }
  }
}

void Database::removeRecord(string name) {
  int mod = (name[1] + name[6] + name[12]) % 47;

  if(names[mod] == 0)
    cout << "No record with that name exists." << endl;
  else {
    Record* current = names[mod];
    Record* previous = 0;

    if(names[mod]->getName() == name)
      names[mod] = current->nextName;
    else {
      while(current->getName() != name) {
        previous = current;
        current = current->nextName;
      }
      previous->nextName = current->nextName;
    }
  }
}

void Database::removeRecord(long number, string name) {
  long mod = number;
  mod = mod / 10000000;
  mod = mod * (mod * 3) % 113;

  if(areaCodes[mod] == 0)
    cout << "No record with that phone number exists." << endl;
  else {
    Record* current = areaCodes[mod];
    Record* previous = 0;

    if(areaCodes[mod]->getName() == name)
      areaCodes[mod] = current->nextAreaCode;
    else {
      while(current->getName() != name) {
        previous = current;
        current = current->nextAreaCode;
      }
      previous->nextAreaCode = current->nextAreaCode;
    }
  }
}

Record* Database::getRecord(long number) {
  long mod = number;
  mod = mod % 10000;
  mod = mod % 53;

  if(numbers[mod] == 0)
    cout << "No record with that phone number exists." << endl;
  else {
    Record* temp = numbers[mod];

    while(temp->getPhoneNumber() != number)
      temp = temp->nextNumber;

    return temp;
  }
}

Record* Database::getRecord(string name) {
  name.replace(name.length() - 1, name.length(), " ");
  while(name.length() != 20) {
    name.append(" ");
  }

  int mod = (name[1] + name[6] + name[12]) % 47;

  if(names[mod] == 0)
    cout << "No record with that name exists." << endl;
  else {
    Record* temp = names[mod];

    while(temp->getName() != name)
      temp = temp->nextName;

    return temp;
  }
}

void Database::printRecordsByName() {
  cout << "-----Records by Name-----" << endl;
  for(int i = 0; i < 47; i++) {
    cout << i << ": ";
    if(names[i] != 0) {
      Record* temp = names[i];
      cout << temp->getName();
      while(temp->nextName != 0) {
        temp = temp->nextName;
        cout << ", " << temp->getName();
      }
    }
    cout << endl;
  }
}

void Database::printRecordsByNumber() {
  cout << "-----Records by Number-----" << endl;
  for(int i = 0; i < 53; i++) {
    cout << i << ": ";
    if(numbers[i] != 0) {
      Record* temp = numbers[i];
      if(temp->getPhoneNumber() == 0)
        cout << "0000000000";
      else
        cout << temp->getPhoneNumber();
      while(temp->nextNumber != 0) {
        temp = temp->nextNumber;
        if(temp->getPhoneNumber() == 0)
          cout << ", 0000000000";
        else
          cout << ", " << temp->getPhoneNumber();
      }
    }
    cout << endl;
  }
}

void Database::printRecordsByAreaCode() {
  cout << "-----Records by Area Code-----" << endl;
  for(int i = 0; i < 113; i++) {
    cout << i << ": ";
    if(areaCodes[i] != 0) {
      Record* temp = areaCodes[i];
      cout << temp->getName();
      while(temp->nextAreaCode != 0) {
        temp = temp->nextAreaCode;
        cout << ", " << temp->getName();
      }
    }
    cout << endl;
  }
}

void Database::modifyBalance(float amount, long number) {
  cout << "Original balance: " << getRecord(number)->getCharge() << endl;
  getRecord(number)->changeBalance(amount);
  cout << "New balance: " << getRecord(number)->getCharge() << endl;
}

void Database::modifyBalance(float amount, string name) {
  cout << "Original balance: " << getRecord(name)->getCharge() << endl;
  getRecord(name)->changeBalance(amount);
  cout << "New balance: " << getRecord(name)->getCharge() << endl;
}

void Database::printRecord(long number) {
  cout << getRecord(number)->getName() << "'s bill: " << getRecord(number)->getCharge() << endl;
}

void Database::printRecord(string name) {
  cout << getRecord(name)->getName() << "'s bill: " << getRecord(name)->getCharge() << endl;
}

void Database::printByHash(int hash) {
  if(names[hash] == 0)
    cout << "No records have a name that hash to: " << hash << endl;
  else {
    Record* temp = names[hash];
    cout << temp->getName() << temp->getAddress() << endl;
    while(temp->nextName != 0) {
      temp = temp->nextName;
      cout << temp->getName() << temp->getAddress() << endl;
    }
  }
}

void Database::printByDays(int day) {
  Record* temp1 = numbers[(day - 2) + day];
  Record* temp2 = numbers[(day - 2) + day - 1];

  if(temp1 == 0 && temp2 == 0) {
    cout << "No records have bill payments on day " << day << " of the month." << endl;
  }
  else if(temp1 == 0) {
    cout << "Bills for day " << day << ": " << endl;
    cout << temp2->getName() << temp2->getAddress() << temp2->getCharge() << endl;
    while(temp2->nextNumber != 0) {
      temp2 = temp2->nextNumber;
      cout << temp2->getName() << temp2->getAddress() << temp2->getCharge() << endl;
    }
  }
  else if(temp2 == 0) {
    cout << "Bills for day " << day << ": " << endl;
    cout << temp1->getName() << temp1->getAddress() << temp1->getCharge() << endl;
    while(temp1->nextNumber != 0) {
      temp1 = temp1->nextNumber;
      cout << temp1->getName() << temp1->getAddress() << temp1->getCharge() << endl;
    }
  }
  else {
    cout << "Bills for day " << day << ": " << endl;
    cout << temp1->getName() << temp1->getAddress() << temp1->getCharge() << endl;
    while(temp1->nextNumber != 0) {
      temp1 = temp1->nextNumber;
      cout << temp1->getName() << temp1->getAddress() << temp1->getCharge() << endl;
    }
    cout << temp2->getName() << temp2->getAddress() << temp2->getCharge() << endl;
    while(temp2->nextNumber != 0) {
      temp2 = temp2->nextNumber;
      cout << temp2->getName() << temp2->getAddress() << temp2->getCharge() << endl;
    }
  }
}

void Database::printbyAreaCode(int areaCode) {
  int mod = areaCode * (areaCode * 3) % 113;

  if(areaCodes[mod] == 0) {
    cout << "No records present for area code: " << areaCode << "." << endl;
  }
  else {
    Record* temp = areaCodes[mod];
    if(temp->getPhoneNumber() / 10000000 == areaCode)
      cout << temp->getName() << temp->getPhoneNumber() << endl;
    while(temp->nextAreaCode != 0) {
      temp = temp->nextAreaCode;
      if(temp->getPhoneNumber() / 10000000 == areaCode)
        cout << temp->getName() << temp->getPhoneNumber() << endl;
    }
  }
}
