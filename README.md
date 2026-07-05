# Mini SQL Engine

A lightweight SQL engine built in **C++** with a **Qt6 GUI** that supports basic SQL operations on in-memory tables. This project was developed to understand how databases internally process SQL queries, manage tables, and store data.

---

## Features

### Table Management
- Create tables
- Drop tables
- View available tables in the GUI

### Data Manipulation
- Insert rows
- Update rows
- Delete rows

### Query Operations
- Display all rows (`SELECT *`)
- Display selected columns
- Filter rows using `WHERE`
  - `==`
  - `!=`
- Sort records using `ORDER BY`
- Count number of records

### Persistence
- Save tables to disk
- Load saved tables

### GUI Features
- Execute SQL queries through an interactive editor
- Output console displaying query results
- Table Explorer panel
- Double-click a table to view its contents
- Right-click a table to delete it
- Automatic refresh of Table Explorer after create/load/drop operations

---

## Technologies Used

- C++
- Qt 6
- CMake
- STL

---

## Project Structure

```
Mini_SQL_engine/
│
├── src/
│   ├── Database.cpp/.h
│   ├── Engine.cpp/.h
│   ├── Parser.cpp/.h
│   ├── Storage.cpp/.h
│   ├── Table.cpp/.h
│   └── Utils.h
│
├── MiniSQLGUI/
│   ├── mainwindow.cpp/.h
│   ├── mainwindow.ui
│   └── CMakeLists.txt
│
└── README.md
```

---

## Supported Commands

### Create Table

```sql
CREATE TABLE Employees ID Name
```

### Insert Data

```sql
INSERT INTO Employees 1 Alice
INSERT INTO Employees 2 Bob
INSERT INTO Employees 3 Charlie
```

### Display Table

```sql
SELECT * FROM Employees
```

### Display Specific Columns

```sql
SELECT ID Name FROM Employees
```

### Filter Records

```sql
SELECT * FROM Employees WHERE Name == Alice
SELECT ID Name FROM Employees WHERE Name != Bob
```

### Update Records

```sql
UPDATE Employees SET Name Alice WHERE ID 1
```

### Delete Records

```sql
DELETE FROM Employees WHERE ID 2
```

### Sort Records

```sql
ORDER Employees BY ID
```

### Count Records

```sql
COUNT Employees
```

### Save Table

```sql
SAVE Employees
```

### Load Table

```sql
LOAD Employees
```

### Drop Table

```sql
DROP TABLE Employees
```

---

## Current Limitations

- Supports only simple SQL syntax.
- Data types are stored as strings.
- `WHERE` currently supports `==` and `!=`.
- No support yet for:
  - JOIN
  - GROUP BY
  - Aggregate functions
  - Multiple conditions (`AND` / `OR`)
  - Primary keys or constraints

---

## Future Improvements

- Support comparison operators (`<`, `>`, `<=`, `>=`)
- Multiple WHERE conditions
- Aggregate functions
- JOIN operations
- CSV import/export
- Better error handling
- Query history
- Keyboard shortcuts

---

## Learning Goals

This project was built to understand:

- SQL query parsing
- Database architecture
- Table management
- Data storage
- GUI application development using Qt
- Object-oriented design in C++

---

## Author

**Arpita Sahu**

A personal project created for learning database internals and C++ application development.