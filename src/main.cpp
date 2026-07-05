#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Database.h"
#include "Parser.h"
int main()
{
    Database db;
    Parser parser;
    string command;

    cout<<"Write your commands below. Type 'exit' to quit."<<endl;
    
    //to get complete command from user input
    while (true)
    {
        getline(cin, command);

        if(command=="exit") break;

        vector<string> tokens = parser.tokenize(command);

        
        if(tokens[0] == "CREATE" && tokens.size() >=4)
        {
            db.createTable(tokens[2], {tokens.begin() + 3, tokens.end()});
        }

        else if(tokens[0] == "INSERT" && tokens.size() >=4)
        {
            db.insertInto(tokens[2], {tokens.begin() + 3, tokens.end()});
        }

        else if(tokens[0]=="SELECT" && tokens.size() >=2)
        {
            if(tokens[1] == "*" && tokens[2] == "FROM")
            {
                db.showTable(tokens[3]);
            }
            else
            {
                int i = 1;
                vector<string> cols;
                while(i < tokens.size() && tokens[i] != "FROM")
                {
                    cols.push_back(tokens[i]);
                    i++;
                }
                if(i == tokens.size())
                {
                    cout<<"invalid command. Please try again."<<endl;
                    continue;
                }
                if(i+1 >= tokens.size())
                {
                    cout<<"missing table name. Please try again."<<endl;
                    continue;
                }
                if(tokens.size() <= i+2)
                {
                    db.showTable(tokens[i+1], cols);
                }
                if(i+2 < tokens.size() && tokens[i+2] == "WHERE")
                {
                    if(i+3 >= tokens.size())
                    {
                        cout<<"missing condition. Please try again."<<endl;
                        continue;
                    }
                    if(i+4 >= tokens.size())
                    {
                        cout<<"missing value for condition. Please try again."<<endl;
                        continue;
                    }
                    db.filterTable(tokens[i+1],cols, tokens[i+3],tokens[i+4]);
                }
            }   
        }
        else if(tokens[0]=="DELETE" && tokens.size()>=6 && tokens[1]=="FROM" && tokens[3]=="WHERE")
        {
            db.deleteFromTable(tokens[2], tokens[4],tokens[5]);
        }
        
        else if(tokens[0]=="UPDATE" && tokens.size()>=8 && tokens[2]=="SET" && tokens[5]=="WHERE")
        {
            db.updateTable(tokens[1], tokens[3], tokens[4], tokens[6], tokens[7]);
        }

        else if(tokens[0] == "SAVE")
        {
            db.saveTable(tokens[1]);
        }
        else if(tokens[0] == "LOAD")
        {
            db.loadTable(tokens[1]);
        }
        else if(tokens[0] == "ORDER")
        {
            if(tokens.size() != 4)
            {
                cout << "Invalid command." << endl;
                continue;
            }

            if(tokens[2] != "BY")
            {
                cout << "Expected BY." << endl;
                continue;
            }

            db.orderTable(tokens[1], tokens[3]);
        }
        else if(tokens[0] == "COUNT")
        {
            db.countTable(tokens[1]);
        }
        else if(tokens[0] == "DROP")
        {
            if(tokens.size() < 3 || tokens[1] != "TABLE")
            {
                cout << "Invalid DROP command." << endl;
                continue;
            }
            db.dropTable(tokens[2]);
        }
        else
        {
            cout<<"invalid command. Please try again."<<endl;
        }
    }
}