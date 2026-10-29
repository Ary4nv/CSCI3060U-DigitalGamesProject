#include "AccountRegistry.h"

// Replaces the accounts in memory with the ones in the accounts file.
// Returns what went wrong if the file can't be opened or has a bad line.
FileLoadStatus AccountRegistry::loadFromFile(const std::string& path) {
    std::vector<std::string> lines;
    FileLoadStatus status = RecordFile::readLines(path, lines);
    if (status != FILE_LOADED) {
        return status;
    }

    std::vector<Account> loadedAccounts;
    for (std::size_t i = 0; i < lines.size(); i++) {
        Account account;
        if (!Account::parseFileLine(lines[i], account)) {
            return FILE_BAD_FORMAT;
        }
        loadedAccounts.push_back(account);
    }

    accounts = loadedAccounts;
    return FILE_LOADED;
}

// Returns the account with this username (case sensitive) or NULL if there isn't one.
Account* AccountRegistry::find(const std::string& username) {
    for (std::size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getUsername() == username) {
            return &accounts[i];
        }
    }
    return NULL;
}

// Adds a new account to the end of the list.
void AccountRegistry::add(const Account& account) {
    accounts.push_back(account);
}

// Removes the account with this username. Returns false if there was none.
bool AccountRegistry::remove(const std::string& username) {
    for (std::size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getUsername() == username) {
            accounts.erase(accounts.begin() + i);
            return true;
        }
    }
    return false;
}

// Returns every account, in file order.
const std::vector<Account>& AccountRegistry::getAll() const {
    return accounts;
}
