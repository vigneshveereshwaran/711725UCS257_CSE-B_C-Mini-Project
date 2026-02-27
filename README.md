🏦 Bank Account Management System (C)
📌 Project Description

This is a Bank Account Management System written in the C programming language.
The program uses random-access file processing to store, update, delete, and retrieve bank account records from a binary file (credit.dat).

It demonstrates practical usage of:

Structures in C

File handling (binary files)

Random access using fseek()

Reading and writing records using fread() and fwrite()

📂 Project Files

main.c – Source code of the program

credit.dat – Binary file storing account records

accounts.txt – Generated formatted text file

README.md – Project documentation

🗂 Structure Used
struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
};

Each record contains:

Account Number

Last Name

First Name

Balance

⚙️ Features

The program provides the following options:

Store formatted text file

Creates accounts.txt for printing

Update an account

Add charge (+)

Make payment (-)

Add a new account

Insert new record into file

Delete an account

Removes existing record

Exit program

🔁 How It Works

The file credit.dat is opened in binary mode (rb+)

The program uses:

fseek() to jump to a specific record

fread() to read data

fwrite() to update data

Each account number corresponds to a fixed position in the file.

Example:

fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);

This allows direct access to any account without reading the entire file.

🛠 How to Compile and Run
Using GCC (Windows / Linux)
gcc main.c -o bank
./bank
If using Windows Command Prompt:
gcc main.c -o bank.exe
bank.exe
📘 Concepts Demonstrated

Random-access files

Binary file handling

Structured data storage

Menu-driven programs

Updating records in-place

📚 Learning Outcome

After completing this project, you will understand:

How databases work at a low level

How file systems store structured records

How to modify data without rewriting the entire file

Real-world usage of C file handling

🚀 Future Improvements

Add password protection

Add transaction history

Add input validation

Convert to graphical interface

Store data in a database (MySQL / SQLite)

👨‍💻 Author

Vignesh
B.E. Computer Science and Engineering