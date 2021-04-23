//Rec 4: Classes - encapsulation and data hiding
// Tracy Zhu

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct AccountStru {
    string accName;
    int accNumber;
};



    
// Task 2
// Define an Account class
class AccountClass1 {
    friend ostream& operator<<(ostream&os, const AccountClass1& myAcc);
    
public:
    AccountClass1(const string& name, int number): accName(name), accNumber(number) {};
    
    //getter
    const string& getName() const {
        return accName;
    }
    
    int getNumber() const{
        return accNumber;
    }
    
private:
    string accName;
    int accNumber;
    };

ostream& operator<<(ostream& os, const AccountClass1& myAcc){
    os << myAcc.accName << ":" << myAcc.accNumber;
    return os;
}



// Task 3
// Define an Account and Transaction classes
class Transaction {
    friend ostream& operator<<(ostream& os, const Transaction& tran);
    
public:
    Transaction(const string& thetype, int theamount) :
        type(thetype),
        amount(theamount)
    {}
private:
    string type;
    int amount;
};




class Account2 {
    friend ostream& operator<<(ostream& os, const Account2& myAcc);
    
public:
    Account2(const string& thename, int thenumber) :
        accName(thename), accNumber(thenumber), balance(0){}
    
    const string& getName() const{
        return accName;
    }
    
    int getNumber() const{
        return accNumber;
    }
    
    void deposit(int amount) {
        balance += amount;
        history.emplace_back("Deposit", amount);
       
    }
    void withdrawl(int amount) {
        if (balance - amount < 0){
            cerr << "\ninsufficient balance" << endl;
        }
        else {
            balance -= amount;
            history.emplace_back("withdrawal", amount);
        }
    }

private:
    string accName;
    int accNumber, balance;
    vector<Transaction> history;
};

ostream& operator <<(ostream& os, const Transaction& tran){
    os << tran.type << ":" << tran.amount << endl;
    return os;
}

ostream& operator <<(ostream& os, const Account2& myAcc){
    os << myAcc.accName << myAcc.accNumber <<":" << endl;
    for (const Transaction& tran : myAcc.history) {
        os << tran;
    }
    return os;
}

// Task 4

class Account3 {
    friend ostream& operator<<(ostream&os, const AccountClass1& myAcc);
    
public:
    Account3(const string& name, int number): accName(name), accNumber(number) {};
    
    //getter
    const string& getName() const{
        return accName;
    }
    
    int getNumber() const{
        return accNumber;
    }
    
    void deposit(int amount) {
        history.emplace_back("deposit", amount);
        balance += amount;
        
    }
    
    void withdrawl(int amount) {
        if (balance - amount < 0){
            cerr << "\ninsufficient balance" << endl;
            
        }
        else {
            balance -= amount;
            history.emplace_back("withdrawal", amount);
        }
    }

    class Transaction {
        friend ostream& operator<<(ostream& os, const Transaction& tran);
    public:
        Transaction (const string& theType, int amount) : type(theType), amount(amount) {};
    
    private:
        string type;
        int amount;
    };
    
    string accName;
    int accNumber;
    vector<Transaction> history;
    int balance = 0;
};

ostream& operator <<(ostream& os, const Account3::Transaction& tran){
    os << tran.type << ":" << tran.amount << endl;
    return os;
}

ostream& operator <<(ostream& os, const Account3& myAcc){
    os << myAcc.accName << ":" << myAcc.accNumber << endl;
    os << "Transaction History:" << endl;
    
    for (const Account3 ::Transaction& tran : myAcc.history) {
        os << tran;
    }
    return os;
}


// Task 5
// Define an Account with a nested private Transaction class

class Account4 {
    friend ostream& operator<<(ostream&os, const Account4& myAcc);
    
public:
    Account4(const string& name, int number): accName(name), accNumber(number) {};
    
    //getter
    const string& getName() const{
        return accName;
    }
    
    int getNumber() const{
        return accNumber;
    }
    
    void deposit(int amount) {
        history.emplace_back("deposit", amount);
        balance += amount;
    }
    
    void withdrawl(int amount) {
        if (balance - amount < 0){
            cerr << "\ninsufficient balance" << endl;

        }
        else {
            balance -= amount;
            history.emplace_back("withdrawal", amount);
        }
    }

    private:
        class Transaction {
            friend ostream& operator<<(ostream& os, const Transaction& trans){
                os << trans.type << ":" << trans.amount<<endl;
                return os;
            }
        
        public:
            Transaction (const string& theType, int amount) : type(theType), amount(amount) {};
        
        private:
            string type;
            int amount;
        };
        
        string accName;
        int accNumber;
        vector<Transaction> history;
        int balance = 0;
    };

ostream& operator<<(ostream& os, const Account4& myAcc){
    os << myAcc.accName << ":" << myAcc.accNumber << endl;
    os << "Transaction History:" << endl;
    
    for(const Account4:: Transaction& myTransaction: myAcc.history){
        os << myTransaction << endl; ;
    }
    return os;
};



int main() {
    
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";

    ifstream ifs("accounts.txt");
    vector<AccountStru> AccountStruVec;
    string name;
    int number;
    if(!ifs){
        cerr << "Could not open the file" << endl;
        exit(1);
    }
    while(ifs >> name >> number) {
        AccountStru myAcc;
        myAcc.accName = name;
        myAcc.accNumber = number;
        AccountStruVec.push_back(myAcc);
    }
    ifs.close();

    for(const AccountStru& myAccS : AccountStruVec){
        cout << myAccS.accName << ": " << myAccS.accNumber << endl;
    }
    cout << endl;


    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";

    AccountStruVec.clear();
    ifs.open("accounts.txt");
    if(!ifs){
        cerr << "Could not open the file" << endl;
        exit(1);
    }
    while(ifs >> name >> number) {
        AccountStru myAcc {name, number};
        AccountStruVec.push_back(myAcc);
    }
    ifs.close();
    
    
    for(const AccountStru& myAccS : AccountStruVec){
        cout << myAccS.accName << ": " << myAccS.accNumber << endl;
    }
    cout << endl;
    
    
    
    
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";


    vector<AccountClass1> AccountClassVec;
    
    ifs.open("accounts.txt");
    while(ifs >> name >> number){
        AccountClass1 myAcc = AccountClass1(name, number);
        AccountClassVec.push_back(myAcc);
    }
    ifs.close();
        
    
    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for (const AccountClass1& account : AccountClassVec) {
        cout << account.getName() << ": " << account.getNumber() << endl;
    }

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    for(const AccountClass1& myAcc : AccountClassVec){
        cout << myAcc << endl;
    }
    
    
    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    AccountClassVec.clear();
    ifs.open("accounts.txt");
    while(ifs >> name >> number){
        AccountClassVec.push_back(AccountClass1(name, number));
    }
    ifs.close();
    for(const AccountClass1& myAcc : AccountClassVec){
        cout << myAcc << endl;
    }


    
    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    AccountClassVec.clear();
    ifs.open("accounts.txt");
    while(ifs >> name >> number){
        AccountClassVec.emplace_back(name, number);
    }
    ifs.close();
    for(const AccountClass1& myAcc : AccountClassVec){
        cout << myAcc << endl;
    }
        
    
    
    
    
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";
    ifs.clear();
    vector<Account2> AccountClassVec2;
    ifs.open("transactions.txt");
    if (!ifs) {
        cerr << "could not open the file";
        exit(1);
    }
    
    string command, accName;
    int  accNum, transAmount;

    
    while(ifs >> command) {

        if (command == "Account") {
            ifs >> accName >> accNum;
            Account2 myAcc2 = Account2(accName, accNum);
            AccountClassVec2.push_back(myAcc2);
        }
        
        else{
            ifs >> accNum >> transAmount;
            
            if (command == "Deposit") {
                for( Account2& acc : AccountClassVec2){
                    if (acc.getNumber() == accNum){
                        acc.deposit(transAmount);
                    }
                }
            }
            
            
            else if (command == "Withdraw") {
                for(Account2& acc : AccountClassVec2){
                    if (acc.getNumber() == accNum){
                        acc.withdrawl(transAmount);
                    }
                }
            }
            
        }
    }
    
    
    
    for(const Account2& myAcc : AccountClassVec2){
        cout << myAcc << endl;
    }
    
    ifs.close();

    
    
    
    
    
    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
    ifs.clear();
    vector<Account3> AccountClassVec3;
    ifs.open("transactions.txt");
    if (!ifs) {
        cerr << "could not open the file";
        exit(1);
    }

    
    while(ifs >> command) {

        if (command == "Account") {
            ifs >> accName >> accNum;
            Account3 myAcc2 = Account3(accName, accNum);
            AccountClassVec3.push_back(myAcc2);
        }
        
        else{
            ifs >> accNum >> transAmount;
            
            if (command == "Deposit") {
                for( Account3& acc : AccountClassVec3){
                    if (acc.getNumber() == accNum){
                        acc.deposit(transAmount);
                    }
                }
            }
            
            
            else if (command == "Withdraw") {
                for(Account3& acc : AccountClassVec3){
                    if (acc.getNumber() == accNum){
                        acc.withdrawl(transAmount);
                    }
                }
            }
            
        }
    }
    
    
    
    for(const Account3& myAcc : AccountClassVec3){
        cout << myAcc << endl;
    }
    
    ifs.close();

    

    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";
    ifs.clear();
    
    vector<Account4> AccountClassVec4;
    ifs.open("transactions.txt");
    if (!ifs) {
        cerr << "could not open the file";
        exit(1);
    }

    
    while(ifs >> command) {

        if (command == "Account") {
            ifs >> accName >> accNum;
            Account4 myAcc2 = Account4(accName, accNum);
            AccountClassVec4.push_back(myAcc2);
        }
        
        else{
            ifs >> accNum >> transAmount;
            
            if (command == "Deposit") {
                for( Account4& acc : AccountClassVec4){
                    if (acc.getNumber() == accNum){
                        acc.deposit(transAmount);
                    }
                }
            }
            
            
            else if (command == "Withdraw") {
                for(Account4& acc : AccountClassVec4){
                    if (acc.getNumber() == accNum){
                        acc.withdrawl(transAmount);
                    }
                }
            }
            
        }
    }
    
    
    
    for(const Account4& myAcc : AccountClassVec4){
        cout << myAcc << endl;
    }
    
    ifs.close();


    
    
}
