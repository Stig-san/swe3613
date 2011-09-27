#include <string>
#include <list>
#include <sqlite3.h>

using namespace std;
#ifndef CONVERSION_H
#define CONVERSION_H

void printmenu();

list<string> getIcd10( sqlite3_stmt *count, sqlite3_stmt *getIcd, string icd9);

void sqlOpen (sqlite3 *db, sqlite3_stmt *getIcd, sqlite3_stmt *count);

#endif
