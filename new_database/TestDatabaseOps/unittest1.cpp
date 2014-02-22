#include "stdafx.h"
#include "CppUnitTest.h"
#include "Database.h"
#include "Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDatabaseOps
{		
	TEST_CLASS(TestDatabaseOps)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
		Database db; 
  
        string title = "Relation 1"; 
        vector<string> keys; 
        vector<string> attributes; 
        vector<string> attribute_types; 
        vector<string> tuple1; 
        vector<string> tuple2; 
        vector<string> tuple3; 
        vector<string> tuple4; 
  
        attributes.push_back("Attribute 1"); 
        attributes.push_back("Attribute 2"); 
        attributes.push_back("Attribute 3"); 
        attributes.push_back("Attribute 4"); 
  
        attribute_types.push_back("CHAR(10)"); 
        attribute_types.push_back("INT"); 
        attribute_types.push_back("DATE"); 
        attribute_types.push_back("FLOAT"); 
  
        keys.push_back("Attribute 1"); 
        keys.push_back("Attribute 3"); 
  
        tuple1.push_back("Allison"); 
        tuple1.push_back("1"); 
        tuple1.push_back("2013-10-10"); 
        tuple1.push_back("12.38"); 
  
        tuple2.push_back("Bill"); 
        tuple2.push_back("2"); 
        tuple2.push_back("2010-08-01"); 
        tuple2.push_back("48.2"); 
  
        tuple3.push_back("Charlotte"); 
        tuple3.push_back("3"); 
        tuple3.push_back("2033-08-08"); 
        tuple3.push_back("65.54"); 
  
        tuple4.push_back("Doug"); 
        tuple4.push_back("4"); 
        tuple4.push_back("2004-06-13"); 
        tuple4.push_back("89.38"); 
  
        db.create(title, attributes, attribute_types, keys); 
        db.insert_tuple(title, tuple1); 
        db.insert_tuple(title, tuple2); 
        db.insert_tuple(title, tuple3); 

		/******************************************************************************************************************/
		/*      If last tuple inserted correctly, first column of last row should be the name "Doug"
		/*		Also, last column of first row should be "12.38"
		/******************************************************************************************************************/
		db.insert_tuple(title, tuple4); 
		Assert::AreEqual(db.get_table(title).get_row(3).at(0), (string) "Doug");
		Assert::AreEqual(db.get_table(title).get_row(0).at(3), (string) "12.38");
		
        vector<string> tuple5; 
        vector<string> tuple6; 
        vector<string> tuple7; 
        vector<string> tuple8; 
      
        tuple5.push_back("Jake"); 
        tuple5.push_back("57"); 
        tuple5.push_back("1991-10-18"); 
        tuple5.push_back("54.32"); 
  
        tuple6.push_back("Joe"); 
        tuple6.push_back("10"); 
        tuple6.push_back("2015-01-05"); 
        tuple6.push_back("85.3"); 
  
        tuple7.push_back("Charlotte"); 
        tuple7.push_back("3"); 
        tuple7.push_back("2033-08-08"); 
        tuple7.push_back("65.54"); 
  
        tuple8.push_back("Doug"); 
        tuple8.push_back("4"); 
        tuple8.push_back("2004-06-13"); 
        tuple8.push_back("89.38"); 
  
        db.create("Relation 2", attributes, attribute_types, keys); 
        db.insert_tuple("Relation 2", tuple5); 
        db.insert_tuple("Relation 2", tuple6); 
        db.insert_tuple("Relation 2", tuple7); 
        db.insert_tuple("Relation 2", tuple8); 
       
         
		/*********************************************************************************************/
		/*		After removing row 1, "Doug" should move up to row 3								 */
		/*********************************************************************************************/
		//db.remove(title, 0);
		Assert::AreEqual(db.get_table(title).get_row(2).at(0), (string) "Doug");
      
        vector<string> attribute; 
        attribute.push_back("Attribute 2"); 
        vector<string> data; 
        data.push_back("55");  

		/*********************************************************************************************/
		/*		Update Attribute 2 on row 3 of relation 1 to '55'									 */
		/*********************************************************************************************/
		db.update(title, attribute, data, 2);
		Assert::AreEqual(db.get_table(title).get_row(2).at(1), (string) "55");
  
          
        /*********************************************************************************************/
		/*		Select Row 3 of relation 1, attribute 2 should again be '55'						 */
		/*********************************************************************************************/ 
		//Assert::AreEqual(db.select("view1", title, 2).get_row(0).at(1), (string) "55"); 
       
		attribute.push_back("Attribute 1");
      
        attributes[0] = "Attribute 5"; 
        attributes[1] = "Attribute 6"; 
        attributes[2] = "Attribute 7"; 
        attributes[3] = "Attribute 8"; 

		/*********************************************************************************************/
		/*		Rename attributes 1-4 of Relation 1. Attribute 2 should now equal "Attribute 6"		 */
		/*********************************************************************************************/
        Assert::AreEqual(db.rename("view3", title, attributes).get_keys().at(1), (string) "Attribute 6");
  
        /*********************************************************************************************/
		/*		Union of Relation 1 and Relation 2. Row 1, columns 1 & 2 should equal "Charlotte" "3"*/
		/*********************************************************************************************/ 
        Assert::AreEqual(db.set_union("view4", title, "Relation 2").get_row(1).at(0), (string) "Charlotte");
		Assert::AreEqual(db.set_union("view4", title, "Relation 2").get_row(1).at(1), (string) "3");
  
        /*********************************************************************************************/
		/*		Set difference of Relation 1 and 2. Row 2, columns 1 & 2 should equal "Joe" "57"	 */
		/*********************************************************************************************/  
        Assert::AreEqual(db.set_difference("view5", title, "Relation 2").get_row(2).at(0), (string) "Joe");
		Assert::AreEqual(db.set_difference("view5", title, "Relation 2").get_row(2).at(1), (string) "57");
   
        db.cross_product("view6", title, "Relation 2"); 
   
        db.insert_view("Relation 2", "view1"); 
  
        db.remove_table("Relation 1"); 
  
        string table_name1 = "Employee table"; 
        vector<string> attribute_name; 
        vector<string>attribute_t1; 
        vector<string> key_1; 
        vector<string>tuple1_1; 
        vector<string>tuple1_2; 
        vector<string>tuple1_3; 
        vector<string>tuple1_4; 
        vector<string>tuple1_5; 
        vector<string>tuple1_6; 
  
        attribute_name.push_back("LastName"); 
        attribute_name.push_back("Department ID"); 
        attribute_t1.push_back("string"); 
        attribute_t1.push_back("int"); 
        key_1.push_back("LastName"); 
        tuple1_1.push_back("Rafferty"); 
        tuple1_1.push_back("31"); 
        tuple1_2.push_back("Jones"); 
        tuple1_2.push_back("33"); 
        tuple1_3.push_back("Heisenberg"); 
        tuple1_3.push_back("33"); 
        tuple1_4.push_back("Robinson"); 
        tuple1_4.push_back("34"); 
        tuple1_5.push_back("Smith"); 
        tuple1_5.push_back("34"); 
        tuple1_6.push_back("John"); 
        tuple1_6.push_back("NULL"); 
        db.create(table_name1, attribute_name, attribute_t1, key_1); 
        db.insert_tuple(table_name1, tuple1_1); 
        db.insert_tuple(table_name1, tuple1_2); 
        db.insert_tuple(table_name1, tuple1_3); 
        db.insert_tuple(table_name1, tuple1_4); 
        db.insert_tuple(table_name1, tuple1_5); 
        db.insert_tuple(table_name1, tuple1_6); 
        string table_name2 = "Departmnet table"; 
        vector<string> attribute2_name; 
        vector<string>attribute_t2; 
        vector<string> key_2; 
        vector<string>tuple2_1; 
        vector<string>tuple2_2; 
        vector<string>tuple2_3; 
        vector<string>tuple2_4; 
        attribute2_name.push_back("Department ID"); 
        attribute2_name.push_back("Department Name"); 
        key_2.push_back("Department ID"); 
        attribute_t2.push_back("int"); 
        attribute_t2.push_back("string"); 
        tuple2_1.push_back("31"); 
        tuple2_1.push_back("Sales"); 
        tuple2_2.push_back("33"); 
        tuple2_2.push_back("Engineering"); 
        tuple2_3.push_back("34"); 
        tuple2_3.push_back("Chemical"); 
        tuple2_4.push_back("35"); 
        tuple2_4.push_back("Marketing"); 
        db.create(table_name2, attribute2_name, attribute_t2, key_2); 
        db.insert_tuple(table_name2, tuple2_1); 
        db.insert_tuple(table_name2, tuple2_2); 
        db.insert_tuple(table_name2, tuple2_3); 
        db.insert_tuple(table_name2, tuple2_4); 
		
		/*********************************************************************************************/
		/*		Natural join on Employee Table and Department Table. Columns 2 and 3 of Row 1		 */
		/*		should be "31" and "Sales"															 */
		/*********************************************************************************************/
		Assert::AreEqual(db.join("join", table_name1, table_name2).get_row(0).at(1), (string) "31");
		Assert::AreEqual(db.join("join", table_name1, table_name2).get_row(0).at(2), (string) "Sales");
		}

    TEST_METHOD(ParserTest)
		{
      Parser p;
      Assert::AreEqual((int)p.getnputType(string(" CREATE TABLE <-select(kind==\"dogs\"animals")), (int)CREATE);
    }
	};
}