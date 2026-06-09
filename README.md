BANK MANAGEMENT SYSTEM (C LANGUAGE)

A file-based Bank Management System developed using the C programming language.
This project simulates real-world banking operations with authentication, account management, transaction tracking, and admin control features.

FEATURES

SECURITY SYSTEM:

System-level login using a common password
Account-level password protection for each user
Admin authentication for sensitive operations
Account lock after multiple failed login attempts
Admin unlock functionality for locked accounts

USER FEATURES:

Create new bank account
Deposit and withdraw money
View personal account details
View personal transaction history
Secure password-protected access

ADMIN FEATURES:

View all accounts
Delete any account
View all transactions
Unlock locked accounts

BANKING FEATURES:

File-based persistent storage (credit.dat)
Transaction logging system (transactions.dat)
Fast record access using fixed-size file structure
Balance update system with real-time saving

FILE STRUCTURE

bank.c -> Main source code file
credit.dat -> Binary file storing account data
transactions.dat -> Binary file storing transaction history

HOW TO COMPILE AND RUN

Compile:
gcc bank.c -o bank

Run:
./bank

DEFAULT CREDENTIALS

System Password:
bank@123

Admin Password:
root123

CORE CONCEPTS USED

File Handling in C (fopen, fread, fwrite, fseek)
Structures
String Handling
Input Validation
Authentication System Design
Role-based Access Control

SECURITY FEATURES

3-attempt login restriction for accounts
Account locking after failed attempts
Admin-controlled unlock system
Role-based access control system

MENU SYSTEM

Create Account
Deposit / Withdraw
View My Account
View My Transactions
Delete Account (Admin)
View All Accounts (Admin)
View All Transactions (Admin)
Unlock Account (Admin)
Exit

LEARNING OUTCOMES

This project helps in understanding:

Real-world banking logic implementation
Secure authentication system design
File-based database handling
Role-based access control system
Data persistence in C programming

LIMITATIONS

Passwords are stored in plain text (not encrypted)
No database system (uses binary files only)
Single-user execution (no multi-user concurrency support)

FUTURE IMPROVEMENTS

Password hashing for security
SQLite database integration
GUI-based interface
Transaction timestamps
Full audit logging system

AUTHOR

Vignesh 

B.E. Computer Science and Engineering  miniproject
