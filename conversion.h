#include <string>
#include <list>
#include <sqlite3.h>

using namespace std;
#ifndef CONVERSION_H
#define CONVERSION_H

void printmenu();

list<string> getIcd10( sqlite3_stmt *count, sqlite3_stmt* getIcd, string icd9);

list<string> byIcd9 (string icd9);
void printlist (list<string> icd10); 

string sanitize (string input);

#endif
