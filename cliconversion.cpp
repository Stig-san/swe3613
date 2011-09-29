#include <iostream>
#include <string>
#include <list>
#include "conversion.h" 

using namespace std;

int main ()
{
  string icd9;
  int menuctrl=0;
  list<string> icd10;
  
  
  
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
      icd10=byIcd9(sanitize(icd9));
      printlist(icd10);
    }
    
    if(menuctrl==9)  // This is a huge hack... Find a better way
      break;

    printmenu();
  } while (menuctrl!=9);

  return 0;
}
