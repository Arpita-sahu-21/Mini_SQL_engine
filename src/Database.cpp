#include "Database.h"
#include "Table.h"
#include <map>
#include <iostream>


string Database::createTable(string name, vector<string> cols)
{
    if (tables.find(name) != tables.end())
    {
        return "Error: Table with name '" + name + "' already exists.";
    }
    Table newTable(name, cols);
    tables[name] = newTable;
    return "Table '" + name + "' created successfully.";
}
string Database::insertInto(string name, vector<string> row)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }
    if(tables[name].insertRow(row))
    {
        return "Row inserted successfully.";
    }
    
    return "Failed to insert row.";
}

string Database::showTable(string name)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }
    return tables[name].displayTable();
}

string Database::showTable(const string& name, const vector<string>& cols)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }
    return tables[name].displayColumn(cols);
}

string Database :: filterTable(const string& name, const vector<string>& cols, const string& columnname,const string& op, const string& condition)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }
    return tables[name].filterColumn(cols, columnname, op, condition);
}

string Database::deleteFromTable(const string& name, const string& columnname, const string& condition)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }
    return tables[name].deleteRow(columnname, condition);
}
string Database::updateTable(const string& name, const string& setColumn, const string& setValue, const string& whereColumn, const string& whereValue)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }
    return tables[name].updateRow(setColumn, setValue, whereColumn, whereValue);
}

string Database::saveTable(const string& name)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }
    return tables[name].saveToFile();
}

string Database::loadTable(const string& name)
{
    if(tables.find(name) == tables.end())
    {
        vector<string> dummy;
        tables.emplace(name, Table(name, dummy));
    }

    return tables[name].loadFromFile();
}
string Database::orderTable(const string& name, const string& columnName)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }
    return tables[name].orderBy(columnName);
}
string Database::countTable(const string& name)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }
    return tables[name].countRows();
}
string Database::dropTable(const string& name)
{
    if(tables.find(name) == tables.end())
    {
        return "Error: Table with name '" + name + "' does not exist.";
    }

    tables.erase(name);

    return "Table '" + name + "' dropped successfully.";
}

vector<string> Database::getTableNames()
{
    vector<string> names;

    for (auto &table : tables)
    {
        names.push_back(table.first);
    }

    return names;
}