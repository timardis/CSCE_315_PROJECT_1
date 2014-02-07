#include "Database.h"
#include <fstream>
 
#include <cctype>
#include <iostream>
#include <iomanip>
#include <stdexcept>
 
/*------------------------------------------------------------------------------------*/
/* QUERY FUNCTIONS */
/*------------------------------------------------------------------------------------*/

void Database::create(string table_name, vector<string> attributes,
                      vector<string> attribute_types, vector<string> keys){
    // check for keys referring to non-existent attributes
    for(unsigned int i = 0; i < keys.size(); ++i) {
        unsigned int matching_count = 0;
        for(unsigned int j = 0; j < attributes.size(); ++j)
            if(keys[i] == attributes[j])
                ++matching_count;
        if(matching_count == 0) {
            string error = "create: key (";
            error += keys[i];
            error += ") does not match any attributes";
            throw runtime_error(error);
        }
    }
    // check for duplicate attributes
    for(unsigned int i = 0; i < attributes.size(); ++i) 
        for(unsigned int j = i + 1; j < attributes.size(); ++j) 
            if(attributes[i] == attributes[j]) {
                string error = "create: duplicate attribute (";
                error += attributes[i];
                throw runtime_error(error);
            }
 
    // check for existing table
    if(get_relation_index(table_name) > -1) {
        string error = "create: table with name (";
        error += table_name;
        error += ") already exists";
        throw runtime_error(error);
    }
 
    // push back empty table to relation list and get reference to table
    RELATIONAL_LIST.push_back(vector<vector<string> >());
    vector<vector<string> >& relation_table = RELATIONAL_LIST[RELATIONAL_LIST.size()-1];
 
    // push back empty row and intialize with title and keys
    relation_table.push_back(vector<string>());
    relation_table[0].push_back(table_name);
    relation_table[0].insert(relation_table[0].end(), keys.begin(), keys.end());
 
    // add attribute names and attribute types
    relation_table.push_back(attributes);
    relation_table.push_back(attribute_types);
}
 
 