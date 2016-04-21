#ifndef DATABASE_H
#define DATABASE_H
#include "Record.h"
#include <fstream>

class Database {
public:
  Database();
  void insert(Record* record, bool isInit);

  void deleteRecord(long number);
  void deleteRecord(string name);

  void modifyBalance(float amount, long number);
  void modifyBalance(float amount, string name);

  void printRecord(long number);
  void printRecord(string name);

  void printByHash(int hash);
  void printByDays(int day);
  void printbyAreaCode(int areaCode);

  void printRecordsByName();
  void printRecordsByNumber();
  void printRecordsByAreaCode();

private:
  Record* names[47];
  Record* numbers[53];
  Record* areaCodes[113];

  Record* getRecord(long number);
  Record* getRecord(string name);

  ofstream output;

  void removeRecord(long number);
  void removeRecord(string name);
  void removeRecord(long number, string name);

  void insertRecordByName(Record* record);
  void insertRecordByNumber(Record* record);
  void insertRecordByAreaCode(Record* record);
};

#endif
