#include "Table.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

Table::Table(string name, vector<string> cols)
{
    tableName = name;
    columns = cols;
}
Table::Table()
{
    tableName = "";
}

bool Table::insertRow(const vector<string>& row)
    {
        if (row.size() != columns.size())
        {
            cerr << "Error: Row size does not match number of columns." << endl;
            return false;
        }
        rows.push_back(row);
        return true;
    }
string Table::displayTable()
    {
        stringstream ss;
        ss << "Table: " << tableName << "\n\n";

        for (const auto& col : columns)
        {
            ss << left << setw(15) << col;
        }
        ss << "\n";

        for (int i = 0; i < columns.size(); i++)
        {
            ss << "---------------";
        }
        ss << "\n";
        for (const auto& row : rows)
        {
            for (const auto& cell : row)
            {
                ss << left << setw(15) << cell;
            }
            ss << "\n";
        }
        return ss.str();
    }
string Table::displayColumn(const vector<string>& cols)
    {
        stringstream ss;
        ss << "Table: " << tableName << "\n";
        vector<int> colIndices;
        for (int j=0;j<cols.size();j++)
        {
            bool found = false;
            for(int i=0;i<columns.size();i++)
            {
                if(columns[i] == cols[j])
                {
                    found = true;
                    ss << left << setw(15) << columns[i];
                    colIndices.push_back(i);
                    break;
                }
            }
            if(!found)
            {
                return "Error: Column '" + cols[j] + "' does not exist in table '" + tableName + "'.";
            }
        }
        ss << "\n";
        for (const auto& row : rows)
        {
            for (const auto& index : colIndices)
            {
                ss << left << setw(15) << row[index];
            }
            ss << "\n";
        }
        return ss.str();
    }

string Table::filterColumn(const vector<string>& cols,const string& columnname,const string& op,const string& condition)
{
    stringstream ss;
    ss << "Table: " << tableName << "\n";

    vector<int> colIndices;

    // Decide which columns to display
    if(cols.empty())
    {
        // SELECT *
        for(int i = 0; i < columns.size(); i++)
        {
            ss << left << setw(15) << columns[i];
            colIndices.push_back(i);
        }
    }
    else
    {
        // SELECT col1 col2 ...
        for(int j = 0; j < cols.size(); j++)
        {
            bool found = false;

            for(int i = 0; i < columns.size(); i++)
            {
                if(columns[i] == cols[j])
                {
                    found = true;
                    ss << left << setw(15) << columns[i];
                    colIndices.push_back(i);
                    break;
                }
            }

            if(!found)
            {
                return "Error: Column '" + cols[j] +
                       "' does not exist in table '" + tableName + "'.";
            }
        }
    }

    ss << "\n";

    // Find WHERE column
    int filterIndex = -1;

    for(int i = 0; i < columns.size(); i++)
    {
        if(columns[i] == columnname)
        {
            filterIndex = i;
            break;
        }
    }

    if(filterIndex == -1)
    {
        return "Error: Column '" + columnname + "' does not exist.";
    }

    // Filter rows
    for(const auto &row : rows)
    {
        bool match = false;

        try
        {
            if(op == "==")
            {
                match = (row[filterIndex] == condition);
            }
            else if(op == "!=")
            {
                match = (row[filterIndex] != condition);
            }
            else if(op == ">")
            {
                match = (stoi(row[filterIndex]) > stoi(condition));
            }
            else if(op == "<")
            {
                match = (stoi(row[filterIndex]) < stoi(condition));
            }
            else if(op == ">=")
            {
                match = (stoi(row[filterIndex]) >= stoi(condition));
            }
            else if(op == "<=")
            {
                match = (stoi(row[filterIndex]) <= stoi(condition));
            }
        }
        catch(const std::exception&)
        {
            return "Error: Numeric comparison can only be used on numeric values.";
        }
        if(match)
        {
            for(int index : colIndices)
            {
                ss << left << setw(15) << row[index];
            }
            ss << "\n";
        }
    }
    return ss.str();
}
string Table::deleteRow(const string& columnname, const string& condition)
{
    int filterIndex = -1;
    for(int i=0;i<columns.size();i++)
    {
        if(columns[i] == columnname)
        {
            filterIndex = i;
            break;
        }
    }
    if(filterIndex == -1)
    {
        return "Error: Column '" + columnname + "' does not exist.";
    }
    auto it = rows.begin();
    while (it != rows.end())
    {
        if ((*it)[filterIndex] == condition)
        {
            it = rows.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return "Rows deleted successfully.";
}

string Table::updateRow(const string& setColumn, const string& setValue, const string& whereColumn, const string& whereValue)
{
    int setIndex = -1;
    int whereIndex = -1;

    for(int i=0;i<columns.size();i++)
    {
        if(columns[i] == setColumn)
        {
            setIndex = i;
        }
        if(columns[i] == whereColumn)
        {
            whereIndex = i;
        }
    }

    if(setIndex == -1)
    {
        return "Error: Column '" + setColumn + "' does not exist.";
    }
    if(whereIndex == -1)
    {
        return "Error: Column '" + whereColumn + "' does not exist.";
    }


    for (auto&row : rows)
    {
        if(row[whereIndex] == whereValue)
        {
            row[setIndex] = setValue;
        }
    }
    return "Rows updated successfully.";
}
string Table::saveToFile()
{
    ofstream file(tableName + ".txt");

    if(!file)
    {
        return "Failed to save table.";
    }

    // save columns
    for(int i=0;i<columns.size();i++)
    {
        file << columns[i];

        if(i != columns.size()-1)
            file << ",";
    }

    file << endl;

    // save rows
    for(const auto& row : rows)
    {
        for(int i=0;i<row.size();i++)
        {
            file << row[i];

            if(i != row.size()-1)
                file << ",";
        }

        file << endl;
    }

    file.close();

    string result = "Table saved successfully.";
    return result;
}
string Table::loadFromFile()
{
    ifstream file(tableName + ".txt");

    if(!file)
    {
        return "Failed to load table.";
    }

    columns.clear();
    rows.clear();

    string line;

    // Read column names
    if(getline(file, line))
    {
        stringstream ss(line);
        string value;
        
        while(getline(ss, value, ','))
        {
            columns.push_back(value);
        }
    }

    // Read rows
    while(getline(file, line))
    {
        vector<string> row;

        stringstream ss(line);
        string value;

        while(getline(ss, value, ','))
        {
            row.push_back(value);
        }

        rows.push_back(row);
    }

    file.close();

    string result = "Table loaded successfully.";
    return result;
}
string Table::orderBy(const string& columnName)
{
    int orderIndex = -1;
    for(int i=0;i<columns.size();i++)
    {
        if(columns[i] == columnName)
        {
            orderIndex = i;
            break;
        }
    }
    if(orderIndex == -1)
    {
        return "Error: Column '" + columnName + "' does not exist.";
    }

    sort(rows.begin(), rows.end(), [orderIndex](const vector<string>& a, const vector<string>& b) 
    {
        return a[orderIndex] < b[orderIndex];
    });
    return displayTable();
}

string Table::countRows()
{
    string result = "Total Rows: " + to_string(rows.size());
    return result;
}