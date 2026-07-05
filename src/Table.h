#ifndef TABLE_H
#define TABLE_H

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Table
{
private:

    string tableName;

    vector<string> columns;

    vector<vector<string>> rows;

public:
    Table();
    Table(string name, vector<string> cols);

    bool insertRow(const vector<string>& row);
    string displayTable();
    string displayColumn(const vector<string>& cols);

    string filterColumn(const vector<string>& cols, const string& columnname, const  string&op, const string& condition);

    string deleteRow(const string& columnname, const string& condition);

    string updateRow(const string& setColumn, const string& setValue, const string& whereColumn, const string& whereValue);

    string saveToFile();

    string loadFromFile();

    string orderBy(const string& columnName);

    string countRows();
};
#endif