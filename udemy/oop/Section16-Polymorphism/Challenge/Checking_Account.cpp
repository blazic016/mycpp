#include "Checking_Account.h"

Checking_Account::Checking_Account(std::string name, double balance)
    : Account {name, balance} {
}

bool Checking_Account::withdraw(double amount) {
    amount += per_check_fee;
    return Account::withdraw(amount);
}

bool Checking_Account::deposit(double amount) {
    return Account::deposit(amount);
}
// VISE MI NE TREBA
// std::ostream &operator<<(std::ostream &os, const Checking_Account &account) {
//     os << "[Checking_Account: " << account.name << ": " << account.balance  << "]";
//     return os;
// }

void Checking_Account::print(std::ostream &os) const { 
    os.precision(2); 
    os << std::fixed;
    os << "[Account: " << name << ": " << balance << "]";
}


