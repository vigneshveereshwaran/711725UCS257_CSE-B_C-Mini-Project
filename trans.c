#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define SYSTEM_PASS "bank@123"
#define ADMIN_PASS  "root123"

// ================= STRUCTURES =================
typedef struct {
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
    char password[20];
    int locked;   // 🔐 0 = active, 1 = locked
} Client;

typedef struct {
    int acc;
    double amt;
} Transaction;

// ================= INPUT VALIDATION =================
int getValidInt(int min, int max)
{
    int x;
    if (scanf("%d", &x) != 1 || x < min || x > max)
    {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return -1;
    }
    return x;
}

double getValidDouble()
{
    double x;
    if (scanf("%lf", &x) != 1)
    {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return 0;
    }
    return x;
}

// ================= LOGIN SYSTEM =================
int verifySystem()
{
    char pass[20];
    printf("Enter system password: ");
    scanf("%19s", pass);

    return strcmp(pass, SYSTEM_PASS) == 0;
}

int verifyAdmin()
{
    char pass[20];
    printf("Enter admin password: ");
    scanf("%19s", pass);

    if (strcmp(pass, ADMIN_PASS) == 0)
        return 1;

    printf("Wrong admin password\n");
    return 0;
}

// ================= TRANSACTIONS =================
void saveTransaction(int acc, double amt)
{
    FILE *fp = fopen("transactions.dat", "ab");
    if (!fp) return;

    Transaction t = {acc, amt};
    fwrite(&t, sizeof(t), 1, fp);
    fclose(fp);
}

void viewUserTransactions(int accNum)
{
    FILE *fp = fopen("transactions.dat", "rb");
    Transaction t;
    int found = 0;

    if (!fp)
    {
        printf("No transactions found\n");
        return;
    }

    printf("\n--- YOUR TRANSACTIONS ---\n");

    while (fread(&t, sizeof(t), 1, fp) == 1)
    {
        if (t.acc == accNum)
        {
            printf("Amount: %.2f\n", t.amt);
            found = 1;
        }
    }

    if (!found)
        printf("No transactions found\n");

    fclose(fp);
}

void viewAllTransactions()
{
    if (!verifyAdmin()) return;

    FILE *fp = fopen("transactions.dat", "rb");
    Transaction t;

    if (!fp)
    {
        printf("No transactions\n");
        return;
    }

    printf("\n--- ALL TRANSACTIONS ---\n");

    while (fread(&t, sizeof(t), 1, fp) == 1)
    {
        printf("Acc:%d Amount: %.2f\n", t.acc, t.amt);
    }

    fclose(fp);
}

// ================= PASSWORD CHECK WITH LOCK =================
int verifyAccountPassword(Client *c)
{
    char pass[20];

    if (c->locked == 1)
    {
        printf("Account is locked. Contact admin.\n");
        return 0;
    }

    for (int i = 0; i < 3; i++)
    {
        printf("Enter account password: ");
        scanf("%19s", pass);

        if (strcmp(pass, c->password) == 0)
            return 1;

        printf("Wrong password (%d attempts left)\n", 2 - i);
    }

    printf("Account locked due to multiple failed attempts.\n");
    c->locked = 1;
    return -1;
}

// ================= ACCOUNT FUNCTIONS =================
void addAccount(FILE *fPtr)
{
    Client c = {0};

    printf("Enter account number (1-100): ");
    int acc = getValidInt(1, 100);
    if (acc == -1) return;

    fseek(fPtr, (acc - 1) * sizeof(Client), SEEK_SET);
    fread(&c, sizeof(Client), 1, fPtr);

    if (c.acctNum != 0)
    {
        printf("Account already exists\n");
        return;
    }

    printf("Enter last name, first name: ");
    scanf("%14s %9s", c.lastName, c.firstName);

    printf("Enter initial balance: ");
    c.balance = getValidDouble();

    printf("Create account password: ");
    scanf("%19s", c.password);

    c.acctNum = acc;
    c.locked = 0;

    fseek(fPtr, (acc - 1) * sizeof(Client), SEEK_SET);
    fwrite(&c, sizeof(Client), 1, fPtr);

    printf("Account created successfully!\n");
}

void updateAccount(FILE *fPtr)
{
    Client c;

    printf("Enter account number: ");
    int acc = getValidInt(1, 100);
    if (acc == -1) return;

    fseek(fPtr, (acc - 1) * sizeof(Client), SEEK_SET);
    fread(&c, sizeof(Client), 1, fPtr);

    if (c.acctNum == 0)
    {
        printf("Account not found\n");
        return;
    }

    if (!verifyAccountPassword(&c))
        return;

    printf("Current balance: %.2f\n", c.balance);
    printf("Enter amount (+/-): ");

    double amt = getValidDouble();
    c.balance += amt;

    saveTransaction(acc, amt);

    fseek(fPtr, -sizeof(Client), SEEK_CUR);
    fwrite(&c, sizeof(Client), 1, fPtr);

    printf("Transaction successful!\n");
}

void viewAccount(FILE *fPtr)
{
    Client c;

    printf("Enter account number: ");
    int acc = getValidInt(1, 100);
    if (acc == -1) return;

    fseek(fPtr, (acc - 1) * sizeof(Client), SEEK_SET);
    fread(&c, sizeof(Client), 1, fPtr);

    if (c.acctNum == 0)
    {
        printf("Account not found\n");
        return;
    }

    if (!verifyAccountPassword(&c))
        return;

    printf("\nAccount: %d\nName: %s %s\nBalance: %.2f\n",
           c.acctNum, c.firstName, c.lastName, c.balance);
}

void deleteAccount(FILE *fPtr)
{
    if (!verifyAdmin()) return;

    Client blank = {0};
    int acc;

    printf("Enter account number to delete: ");
    acc = getValidInt(1, 100);
    if (acc == -1) return;

    fseek(fPtr, (acc - 1) * sizeof(Client), SEEK_SET);
    fwrite(&blank, sizeof(Client), 1, fPtr);

    printf("Account deleted\n");
}

void printAll(FILE *fPtr)
{
    if (!verifyAdmin()) return;

    Client c;
    rewind(fPtr);

    printf("\n--- ALL ACCOUNTS ---\n");

    while (fread(&c, sizeof(Client), 1, fPtr) == 1)
    {
        if (c.acctNum != 0)
        {
            printf("%d %s %s %.2f %s\n",
                   c.acctNum,
                   c.firstName,
                   c.lastName,
                   c.balance,
                   c.locked ? "LOCKED" : "ACTIVE");
        }
    }
}

// ================= ADMIN UNLOCK =================
void unlockAccount(FILE *fPtr)
{
    if (!verifyAdmin()) return;

    int acc;
    printf("Enter account number to unlock: ");
    acc = getValidInt(1, 100);
    if (acc == -1) return;

    Client c;

    fseek(fPtr, (acc - 1) * sizeof(Client), SEEK_SET);
    fread(&c, sizeof(Client), 1, fPtr);

    if (c.acctNum == 0)
    {
        printf("Account not found\n");
        return;
    }

    c.locked = 0;

    fseek(fPtr, (acc - 1) * sizeof(Client), SEEK_SET);
    fwrite(&c, sizeof(Client), 1, fPtr);

    printf("Account unlocked successfully\n");
}

// ================= MENU =================
void menu()
{
    printf("\n=================================\n");
    printf("     BANK MANAGEMENT SYSTEM\n");
    printf("=================================\n");
    printf("1. Create Account\n");
    printf("2. Deposit / Withdraw\n");
    printf("3. View My Account\n");
    printf("4. View My Transactions\n");
    printf("5. Delete Account (Admin)\n");
    printf("6. View All Accounts (Admin)\n");
    printf("7. View All Transactions (Admin)\n");
    printf("8. Unlock Account (Admin)\n");
    printf("9. Exit\n");
    printf("=================================\n");
    printf("Enter choice: ");
}

// ================= MAIN =================
int main()
{
    FILE *fPtr = fopen("credit.dat", "rb+");

    if (!fPtr)
    {
        fPtr = fopen("credit.dat", "wb+");
        Client blank = {0};

        for (int i = 0; i < MAX; i++)
            fwrite(&blank, sizeof(Client), 1, fPtr);
    }

    if (!verifySystem())
    {
        printf("Access denied\n");
        return 0;
    }

    int choice;

    while (1)
    {
        menu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            break;
        }

        switch (choice)
        {
            case 1: addAccount(fPtr); break;
            case 2: updateAccount(fPtr); break;
            case 3: viewAccount(fPtr); break;
            case 4:
            {
                int acc;
                printf("Enter account number: ");
                acc = getValidInt(1, 100);
                if (acc != -1)
                    viewUserTransactions(acc);
                break;
            }
            case 5: deleteAccount(fPtr); break;
            case 6: printAll(fPtr); break;
            case 7: viewAllTransactions(); break;
            case 8: unlockAccount(fPtr); break;
            case 9: fclose(fPtr); return 0;
            default: printf("Invalid choice\n");
        }
    }

    fclose(fPtr);
    return 0;
}