#include "Engine.h"

string Engine::execute(string command)
{       
    vector<string> tokens = parser.tokenize(command);

    if(tokens.empty())
    {
        return "Please enter a command.";
    }

    //return "FIRST TOKEN = " + tokens[0];
        
        if(tokens[0] == "CREATE" && tokens.size() >=4)
        {
            //return "CREATE branch";
            return db.createTable(tokens[2], {tokens.begin() + 3, tokens.end()});
        }

        else if(tokens[0] == "INSERT" && tokens.size() >=4)
        {
            //return "INSERT branch";
            return db.insertInto(tokens[2], {tokens.begin() + 3, tokens.end()});
        }

        //return "Invalid command.";

        else if(tokens[0]=="SELECT" && tokens.size() >=2)
        {
            if(tokens[1] == "*" && tokens[2] == "FROM")
            {
                if(tokens.size() == 4) return db.showTable(tokens[3]);

                if(tokens.size() >= 8 && tokens[4] == "WHERE")
                {
                    vector<string> cols;

                    return db.filterTable(
                        tokens[3],
                        cols,
                        tokens[5],
                        tokens[6],
                        tokens[7]
                    );
                }

                return "Invalid SELECT command.";
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
                    return "invalid command. Please try again.";
                }
                if(i+1 >= tokens.size())
                {
                    return "missing table name. Please try again.";
                }
                if(tokens.size() <= i+2)
                {
                    return db.showTable(tokens[i+1], cols);
                }
                
                if(i+2 < tokens.size() && tokens[i+2] == "WHERE")
                {
                    if(i+5 >= tokens.size())
                    {
                        return "Invalid WHERE clause.";
                    }

                    return db.filterTable(
                        tokens[i+1],   // table name
                        cols,
                        tokens[i+3],   // column name
                        tokens[i+4],   // operator
                        tokens[i+5]    // value
                    );
                } 
            }            
        }

        else if(tokens[0]=="DELETE" && tokens.size()>=6 && tokens[1]=="FROM" && tokens[3]=="WHERE")
        {
            return db.deleteFromTable(tokens[2], tokens[4],tokens[5]);
        }
        
        else if(tokens[0]=="UPDATE" && tokens.size()>=8 && tokens[2]=="SET" && tokens[5]=="WHERE")
        {
            return db.updateTable(tokens[1], tokens[3], tokens[4], tokens[6], tokens[7]);
        }

        else if(tokens[0] == "SAVE")
        {
            return db.saveTable(tokens[1]);
        }
        else if(tokens[0] == "LOAD")
        {
            return db.loadTable(tokens[1]);
        }
        else if(tokens[0] == "ORDER")
        {
            if(tokens.size() != 4)
            {
                return "Invalid command.";
            }

            if(tokens[2] != "BY")
            {
                return "Expected BY.";
            }

            return db.orderTable(tokens[1], tokens[3]);
        }
        else if(tokens[0] == "COUNT")
        {
            return db.countTable(tokens[1]);
        }
        else if(tokens[0] == "DROP")
        {
            if(tokens.size() < 3 || tokens[1] != "TABLE")
            {
                return "Invalid DROP command.";
            }
            return db.dropTable(tokens[2]);
        }       
        else return "Invalid command.";      
}
vector<string> Engine::getTableNames()
{
    return db.getTableNames();
}

string Engine::dropTable(string tableName)
{
    return db.dropTable(tableName);
}