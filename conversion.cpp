#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <sqlite3.h>
#include "conversion.h"


using namespace std;


void printlist(list<string> icd10)
  {
    while(! icd10.empty())
    {
      cout<<icd10.front()<<endl;
      icd10.pop_front();
    }
  }
  
void printmenu ()
{
  cout<<"What would you like to do?"<<endl;
  cout<<"1: Convert an ICD-9 code to an ICD-10 code"<<endl;
  cout<<"2: Search for codes by description"<<endl;
  cout<<"9: Quit"<<endl;
}

list<string> getIcd10(sqlite3_stmt* count, sqlite3_stmt* getIcd, string icd9)
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
    }
    sqlite3_reset(count);
    sqlite3_reset(getIcd);
      
    return icd10;
   }



list<string> byIcd9(string icd9)
  {
     list<string> output;
     sqlite3 *db;
     sqlite3_open("icd.db", &db);
     sqlite3_stmt *getIcd, *count;
     char sql[75];
     char sql2[75];          // condense using the first char array?
     sprintf(sql, "%s","SELECT Icd10 FROM Convert WHERE Icd9=?");
     sprintf(sql2, "%s","SELECT COUNT(Icd10) FROM Convert WHERE Icd9=?");  // Make this a second column of the above?
     sqlite3_prepare_v2(db,sql,-1,&getIcd,0);

     sqlite3_prepare_v2(db,sql2,-1,&count,0);
     output=getIcd10(count,getIcd,icd9);
     sqlite3_finalize(getIcd);
     sqlite3_finalize(count);
     sqlite3_close(db);
     return output;
  }
  

string sanitize(string input)
  {
 
    for(int i=0; i<input.size(); i++)
    {
      if( input[i] == '-'|| input[i]== ';' || input[i]==':')
      {
        input.erase(i,1);
        i--;              // When erasing everything is shifted left by one
      }
    }
 
    return input;
 
  }


int setDx(string icd, string dx, int kind )
  {

     // return codes: 0-returned normally, 1-incorrect kind 2-DX code already in use

     string table; 
     string id="Id";
     sqlite3 *db;
     sqlite3_open("icd.db", &db);
     sqlite3_stmt *update;
     char sql[75];
     sprintf(sql, "%s","Update ? Set DX=? WHERE ?=?");
     sqlite3_prepare_v2(db,sql,-1,&update,0);
     
     if(kind!=9 || kind!=10)
     {     
       sqlite3_finalize(update);
       sqlite3_close(db); 
       return 1;   // Throw an error MSG on the GUI?
     }
 
     else if(kind==9)
     {
       table="Icd9";
     }

     else
     {
       table="Icd10";
     }
        sqlite3_bind_text(update,1,table.c_str(),-1,SQLITE_STATIC);
        sqlite3_bind_text(update,2,dx.c_str(),-1,SQLITE_STATIC);
        sqlite3_bind_text(update,3,id.c_str(),-1,SQLITE_STATIC);
        sqlite3_bind_text(update,4,icd.c_str(),-1,SQLITE_STATIC); 
        sqlite3_step(update);
        sqlite3_reset(update);
     
 
 
     sqlite3_finalize(update);
     sqlite3_close(db);
     return 0;
  }

string getDesc(string icd, int kind)
{
  
  string table;
  string id="Id";
  sqlite3 *db;
  sqlite3_open("icd.db", &db);
  sqlite3_stmt *getDesc;
  char sql[75];
  sprintf(sql, "%s","SELECT Desc FROM ? WHERE ?=?");
  if(kind!=9 || kind!=10)
  {     
     sqlite3_finalize(getDesc);
     sqlite3_close(db); 
     return "ERROR";   // Throw an error MSG on the GUI?
  }
 
  else if(kind==9)
  {
    table="Icd9";
  }
  else
  {
    table="Icd10";
  }
    sqlite3_bind_text(getDesc,1,table.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(getDesc,2,id.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(getDesc,3,icd.c_str(),-1,SQLITE_STATIC);
    sqlite3_step(getDesc);
    sqlite3_reset(getDesc);

}
 
