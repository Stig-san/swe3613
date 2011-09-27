#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <sqlite3.h>
#include "conversion.h"


using namespace std;

void printmenu ()
{
  cout<<"What would you like to do?"<<endl;
  cout<<"1: Convert an ICD-9 code to an ICD-10 code"<<endl;
  cout<<"9: Quit"<<endl;
}

list<string> getIcd10(sqlite3_stmt* count, sqlite3_stmt *getIcd, string icd9)
  {
    int counter;
    list<string> icd10;
 
    sqlite3_bind_text(count,1,icd9.c_str(),-1,SQLITE_STATIC);
    sqlite3_step(count);
    counter= sqlite3_column_int(count,0);
    sqlite3_bind_text(getIcd,1,icd9.c_str(),-1,SQLITE_STATIC);
    for(int i=0; i<counter; i++)
    {
      sqlite3_step(getIcd);             
      icd10.push_back( (const char*) sqlite3_column_text(getIcd,0));
      cout<<icd10.back()<<endl;
    }
    sqlite3_reset(count);
    sqlite3_reset(getIcd);

    return icd10;
   }

int main ()
{
  string icd9;
  sqlite3 *db;
  int menuctrl=0;
  list<string> icd10;

  sqlite3_open("icd.db", &db);
  sqlite3_stmt *getIcd, *count;
 
  char sql[75];
  char sql2[75];          // condense using the first char array?
  sprintf(sql, "%s","SELECT Icd10 FROM Convert WHERE Icd9=?");
  sprintf(sql2, "%s","SELECT COUNT(Icd10) FROM Convert WHERE Icd9=?");  // Make this a second column of the above?
  sqlite3_prepare_v2(db,sql,-1,&getIcd,0);
  sqlite3_prepare_v2(db,sql2,-1,&count,0);
  
  
  
  
  cout<<"Welcome to icd9 to icd10 conversion!"<<endl;
  printmenu();
  do
  {
    while( ! (cin>>menuctrl))
    {
       cout<<"Please use a number"<<endl;
      cin.clear();
      cin.ignore(1000, '\n');
    }
    if(menuctrl==1)
    {                   
      cout<<"Please enter the ICD-9 code to convert:";
      cin>>icd9;
      icd10=getIcd10(count,getIcd, icd9);
    }
    
    if(menuctrl==9)  // This is a huge hack... Find a better way
      break;

    printmenu();
  } while (menuctrl!=9);

  sqlite3_finalize(getIcd);
  sqlite3_finalize(count);
  sqlite3_close(db);
  return 0;
}

 
 
