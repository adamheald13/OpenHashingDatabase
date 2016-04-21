#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "Record.h"
#include "Database.h"
using namespace std;

void populateDb();
void runTest(char* filename);

Database db;

int main(int argc, char* argv[]) {
  if(argc != 2) {
    cerr << "Usage: " << argv[0] << " <FILE>" << endl;
    return 1;
  }

  string filename(argv[1]);
  filename = filename + "_output.txt";
  const char* file = filename.c_str();

  freopen(file, "w", stdout);
  // db.initStream(temp);

  populateDb();
  runTest(argv[1]);
  // db.printRecordsByName();
  // db.printRecordsByNumber();
  // db.printRecordsByAreaCode();

  return 0;
}

void populateDb() {
  ifstream phonebook;
  phonebook.open("phonebook.txt");

  char name[20];
  char address[26];
  char number[14];
  char charge[9];

  if(phonebook.is_open()) {
    for(int j = 0; j < 200; j++) {
      char ch;

      for(int i = 0; i < 20; i++) {
        phonebook >> noskipws >> ch;
        name[i] = ch;
      }
      string nameString(name);
      phonebook >> noskipws >> ch;

      for(int i = 0; i < 25; i++) {
        phonebook >> noskipws >>ch;
        address[i] = ch;
      }
      address[25] = '\0';
      string addressString(address);
      phonebook >> noskipws >> ch;
      phonebook >> noskipws >> ch;

      for(int i = 0; i < 14; i++)
        phonebook >> noskipws >> number[i];

      for(int i = 0; i < 9; i++) {
        phonebook >> noskipws >> ch;
        if(isdigit(ch) || ch == '.') {
          charge[i] = ch;
        }
        else {
            phonebook >> noskipws >> ch;
          for(int k = i; k < 9; k++) {
            charge[k] = '\0';
          }
          i = 9;
        }
      }

      string temp1 = number;
      string temp2 = charge;

      long numberLong = atol(temp1.c_str());
      float chargeFloat = atof(temp2.c_str());

      // cout << nameString << endl
      //      << addressString << endl
      //      << numberLong << endl
      //      << chargeFloat << endl;

      db.insert(new Record(nameString, addressString, numberLong, chargeFloat), true);
    }
  }

  phonebook.close();
}

void runTest(char* filename) {
  ifstream testFile;
  testFile.open(filename);

  int option;
  string optionString;
  getline(testFile, optionString);

  option = atoi(optionString.c_str());

  while(option != 12) {
    string input;
    getline(testFile, input);

    stringstream s1;
    stringstream s2;

    string temp;
    string name;
    string address;
    long number;
    float charge;
    int hash;
    int day;
    int areaCode;

    switch(option) {
      case 1:
        cout << "----- Option 1 -----" << endl;
        name = input.substr(0, 20);
        address = input.substr(21, 25);
        temp = input.substr(46, 34);
        s1 << temp;
        s1 >> number >> charge;
        db.insert(new Record(name, address, number, charge), false);
        break;
      case 2:
        cout << "----- Option 2 -----" << endl;
        s1 << input;
        s1 >> number;
        name = input.substr(11, 20);
        address = input.substr(32, 25);
        temp = input.substr(57, 13);
        s2 << temp;
        s2 >> charge;
        db.insert(new Record(name, address, number, charge), false);
        break;
      case 3:
        cout << "----- Option 3 -----" << endl;
        db.deleteRecord(input);
        break;
      case 4:
        cout << "----- Option 4 -----" << endl;
        number = atol(input.c_str());
        db.deleteRecord(number);
        break;
      case 5:
        cout << "----- Option 5 -----" << endl;
        s1 << input;
        s1 >> charge;
        s1 >> number;
        if(number != 0)
          db.modifyBalance(-charge, number);
        else {
          s2 << input;
          s2 >> temp;
          name = input.substr(temp.length() + 1, 20);
          db.modifyBalance(-charge, name);
        }
        break;
      case 6:
        cout << "----- Option 6 -----" << endl;
        s1 << input;
        s1 >> charge;
        s1 >> number;
        if(number != 0)
          db.modifyBalance(charge, number);
        else {
          s2 << input;
          s2 >> temp;
          name = input.substr(temp.length() + 1, 20);
          db.modifyBalance(charge, name);
        }
        break;
      case 7:
        cout << "----- Option 7 -----" << endl;
        name = input;
        db.printRecord(name);
        break;
      case 8:
        cout << "----- Option 8 -----" << endl;
        number = atol(input.c_str());
        db.printRecord(number);
        break;
      case 9:
        cout << "----- Option 9 -----" << endl;
        hash = atoi(input.c_str());
        db.printByHash(hash);
        break;
      case 10:
        cout << "----- Option 10 -----" << endl;
        day = atoi(input.c_str());
        db.printByDays(day);
        break;
      case 11:
        cout << "----- Option 11 -----" << endl;
        areaCode = atoi(input.c_str());
        db.printbyAreaCode(areaCode);
        break;
    }

    getline(testFile, optionString);
    option = atoi(optionString.c_str());
  }
}
