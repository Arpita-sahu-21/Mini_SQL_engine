#include "Parser.h"
#include <sstream>

vector<string> Parser::tokenize(string command)
{
    vector<string> tokens;

    stringstream ss(command);

    string word;

    while(ss >> word)
    {
        tokens.push_back(word);
    }

    return tokens;
}