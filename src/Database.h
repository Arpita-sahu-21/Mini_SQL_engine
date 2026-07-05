#ifndef DATABASE_H
#define DATABASE_H

#include<iostream>
#include<vector>
#include<string>
#include "Table.h"
#include <map>
using namespace std;

class Database
{
private:

    map<string,Table> tables;

public:

    string createTable(string name, vector<string> cols);

    string insertInto(string name, vector<string> row);

    string showTable(string name);

    string showTable(const string& name, const vector<string>& cols);

    string filterTable(const string& name, const vector<string>& cols, const string& columnname, const  string&op, const string& condition);

    string deleteFromTable(const string& name, const string& columnname, const string& condition);

    string updateTable(const string& name, const string& setColumn, const string& setValue, const string& whereColumn, const string& whereValue);

    string saveTable(const string& name);

    string loadTable(const string& name);

    string orderTable(const string& name, const string& columnName);

    string countTable(const string& name);

    string dropTable(const string& name);

    vector<string> getTableNames();
};

#endif