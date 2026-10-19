#include "ListAccountsTransaction.h"
#include <vector>
#include "FieldFormat.h"
#include "Messages.h"

// Makes a listaccounts transaction.
ListAccountsTransaction::ListAccountsTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Only admins can list accounts.
bool ListAccountsTransaction::isPermittedFor(const Account& user) const {
    return user.isAdmin();
}

// Prints a heading and one "username | type | credit" line per account.
void ListAccountsTransaction::execute() {
    const std::vector<Account>& accounts = session.getAccounts().getAll();

    console.show(Messages::ACTIVE_ACCOUNTS_HEADING);
    for (std::vector<Account>::size_type i = 0; i < accounts.size(); i++) {
        console.show(accounts[i].getUsername() + Messages::LIST_COLUMN_SEPARATOR
                     + accounts[i].getType() + Messages::LIST_COLUMN_SEPARATOR
                     + FieldFormat::moneyDisplay(accounts[i].getCredit()));
    }
}
