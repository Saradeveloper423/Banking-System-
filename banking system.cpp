#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// Function declarations
void displayMenu();

double deposit(double balance);

double withdraw(double balance);

void sendCash(int senderIndex, string names[], int accNumbers[], double balances[], int size);

void checkBalance(string name, int accNumber, double balance);

// Main function
int main()
{
    // User details
    int size = 3;

    string names[3] = {
        "Thabo Mokoena",
        "Lerato Ndlovu",
        "Sipho Khumalo"};
    
    //array of account numbers
    int accNumbers[3] = {1001, 1002, 1003};
    //array of pins associated with each account
    int pins[3] = {1234, 5678, 4321};
    //array of balances associated with each account
    double balances[3] = {2500.00, 1500.50, 5000.00};

    int enteredAcc;
    int enteredPin;
    int currentUser = -1;

    cout << "== == = WELCOME TO GCC BANK == == =" << endl;

    // Login (3 attempts)
    for (int attempt = 1; attempt <= 3; attempt++)
    {
        cout << "\nEnter Account Number : ";
        cin >> enteredAcc;

        cout << "Enter PIN : ";
        cin >> enteredPin;

        // Check user details
        for (int i = 0; i < size; i++)
        {
            if (accNumbers[i] == enteredAcc &&
                pins[i] == enteredPin)
            {
                currentUser = i;
                break;
            }
        }

        if (currentUser != -1)
        {
            break;
        }
        else
        {
            cout << "Wrong Account Number or PIN.Try again." << endl;
        }
    }

    // Stop program if login fails
    if (currentUser == -1)
    {
        cout << "Too many failed attempts.Exiting program." << endl;
        Sleep(3000); // Pause for 3 seconds

        return 0;
    }

    cout << "\nWelcome, " << names[currentUser] << "!" << endl;

    int choice = 0;

    // Main menu loop
    while (choice != 5)
    {
        displayMenu();
        cin >> choice;

        if (choice == 1)
        {
            balances[currentUser] =
                deposit(balances[currentUser]);
        }

        else if (choice == 2)
        {
            balances[currentUser] =
                withdraw(balances[currentUser]);
        }

        else if (choice == 3)
        {
            sendCash(currentUser, names, accNumbers, balances, size);
        }

        else if (choice == 4)
        {
            checkBalance(names[currentUser], accNumbers[currentUser], balances[currentUser]);
        }

        else if (choice == 5)
        {
            cout << "Thank you for using GCC Bank. Goodbye!" << endl;
            Sleep(3000); // Pause for 3 seconds
        }

        else
        {
            cout << "Invalid choice !Please enter a number "<< "from 1 to 5." << endl;
        }
    }

    return 0;
}
// 1. Function to display the menu
void displayMenu()
{
    cout << "\n == == = GCC BANK == == =" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Send Cash" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter choice : ";
}
// 2. Function to deposit money
double deposit(double balance)
{
    double amount;
    cout << "Enter amount to deposit : R";
    cin >> amount;
    if(amount > 0)
    {
        balance = balance + amount;

        cout << "Deposit successful !" << endl;
        cout << "New balance : R" << balance << endl;
    }
    else
    {
        cout << "Invalid amount !Deposit must be more than 0."<< endl;
    }

    return balance;
}

// 3. Function to withdraw money
double withdraw(double balance)
{
    double amount;

    cout << "Enter amount to withdraw : R";
    cin >> amount;

    if(amount <= 0)
    {
        cout << "Invalid amount !Withdrawal must be more " << "than 0." << endl;
    }

    else if (amount > balance)
    {
        cout << "Insufficient funds !Your balance is R" << balance << endl;
    }

    else
    {
        balance = balance - amount;

        cout << "Withdrawal successful !" << endl;
        cout << "New balance : R" << balance << endl;
    }

    return balance;
}

// 4. Function to send cash to another user
void sendCash(int senderIndex, string names[], int accNumbers[], double balances[], int size)
{
    int recipientAcc;
    int recipientIndex = -1;

    cout << "Enter recipient Account Number : ";
    cin >> recipientAcc;

    // Prevent sending cash to own account
    if(recipientAcc == accNumbers[senderIndex])
    {
        cout << "Error : You cannot send cash to your own account."<< endl;

        return;
    }

    // Search for recipient account
    for(int i = 0; i < size; i++)
    {
        if(accNumbers[i] == recipientAcc)
        {
            recipientIndex = i;
            break;
        }
    }

    // Check if account exists
    if(recipientIndex == -1)
    {
        cout << "Error : Account number not found."<< endl;

        return;
    }

    double amount;

    cout << "Enter amount to send to " << names[recipientIndex] << ": R";

    cin >> amount;

    if(amount <= 0)
    {
        cout << "Invalid amount !Must be more than 0."<< endl;
    }

    else if (amount > balances[senderIndex])
    {
        cout << "Insufficient funds !Your balance is R" << balances[senderIndex] << endl;
    }

    else
    {
        // Deduct money from sender
        balances[senderIndex] = balances[senderIndex] - amount;

        // Add money to recipient
        balances[recipientIndex] = balances[recipientIndex] + amount;

        cout << "Successfully sent R" << amount<< " to " << names[recipientIndex] << endl;

        cout << "Your new balance : R"<< balances[senderIndex]<< endl;
    }
}

// 5. Function to check balance
void checkBalance(string name, int accNumber, double balance)
{
    cout << "\n-- - ACCOUNT BALANCE-- -" << endl;
    cout << "\n" << endl;
    cout << "Name : " << name << endl;
    cout << "Account Number : " << accNumber << endl;
    cout << "Current Balance : R" << balance << endl;
}