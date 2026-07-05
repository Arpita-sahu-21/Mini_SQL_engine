#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "Database.h"
#include "Parser.h"

using namespace std;

class Engine
{
private:
    Database db;
    Parser parser;

public:
    string execute(string command);
    
    vector<string> getTableNames();

    string dropTable(string tableName);
};

#endif