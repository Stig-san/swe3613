#include <iostream>
#include <string>
#include <list>
#include <sqlite3.h>
#include <gtest/gtest.h>
#include "conversion.h"

using namespace std;

string icd10TestCode;
list<string> icd10TestCodeList;
string icd10ActualCode;
list<string> icd10ActualCodeList;

TEST(ConversionTest, OneToOne)
{
	sqlite3_stmt *getIcd, *count;
	sqlite3 *db;
	sqlite3_open("icd.db", &db);

	char sql[75];
  	char sql2[75];
  	sprintf(sql, "%s","SELECT Icd10 FROM Convert WHERE Icd9=?");
 	sprintf(sql2, "%s","SELECT COUNT(Icd10) FROM Convert WHERE Icd9=?");
 	sqlite3_prepare_v2(db,sql,-1,&getIcd,0);
 	sqlite3_prepare_v2(db,sql2,-1,&count,0);
 	icd10TestCodeList.push_back("A000");
	icd10ActualCodeList = getIcd10(count,getIcd,"0010");					//Item from function to compare with
	EXPECT_EQ(icd10TestCodeList.back(), icd10ActualCodeList.back());
	icd10TestCodeList.clear();
}

TEST(ConversionTest, OneToMany)
{
	sqlite3_stmt *getIcd, *count;
	sqlite3 *db;
	sqlite3_open("icd.db", &db);

	char sql[75];
  	char sql2[75];
  	sprintf(sql, "%s","SELECT Icd10 FROM Convert WHERE Icd9=?");
  	sprintf(sql2, "%s","SELECT COUNT(Icd10) FROM Convert WHERE Icd9=?");
  	sqlite3_prepare_v2(db,sql,-1,&getIcd,0);
  	sqlite3_prepare_v2(db,sql2,-1,&count,0);
	icd10TestCodeList.push_back("A0100");									//Assigning Test code to a list
	icd10TestCodeList.push_back("A0101");
	icd10TestCodeList.push_back("A0102");
	icd10TestCodeList.push_back("A0103");
	icd10TestCodeList.push_back("A0104");
	icd10TestCodeList.push_back("A0105");
	icd10TestCodeList.push_back("A0109");
	icd10ActualCodeList = getIcd10(count,getIcd,"0020");						//Assigning Actual code to a list
	while(!icd10TestCodeList.empty())
	{
		icd10TestCode = icd10TestCodeList.back();							//Assign Test code from list to string
		icd10ActualCode = icd10ActualCodeList.back();						//Assign Actual code from list to string
		EXPECT_EQ(icd10TestCode, icd10ActualCode);
		icd10TestCodeList.pop_back();
		icd10ActualCodeList.pop_back();
	}
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
