#ifndef ACCOUNTREGISTRY_H
#define ACCOUNTREGISTRY_H

#include <string>
#include <vector>
#include "Account.h"
#include "RecordFile.h"

// All the user accounts that exist during a session. It loads them from the
// user accounts file and lets transactions look up, add and remove accounts.
class AccountRegistry {
public:
    // Replaces the accounts in memory with the ones in the accounts file.
    // Returns what went wrong if the file can't be opened or has a bad line.
    FileLoadStatus loadFromFile(const std::string& path);
    // Returns the account with this username (case sensitive) or NULL if there isn't one.
    Account* find(const std::string& username);
    // Adds a new account to the end of the list.
    void add(const Account& account);
    // Removes the account with this username. Returns false if there was none.
    bool remove(const std::string& username);
    // Returns every account, in file order.
    const std::vector<Account>& getAll() const;

private:
    std::vector<Account> accounts;
};

#endif
