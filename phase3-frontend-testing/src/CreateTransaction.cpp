#include "CreateTransaction.h"
#include "Constants.h"
#include "Messages.h"

// Makes a create transaction.
CreateTransaction::CreateTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Only admins can create accounts.
bool CreateTransaction::isPermittedFor(const Account& user) const {
    return user.isAdmin();
}

// Asks for the new username and account type, checks both, adds the
// account with 0 credit and records a create (01) line.
void CreateTransaction::execute() {
    std::string username;
    if (!console.ask(Messages::NEW_USERNAME_PROMPT, username)) {
        return;
    }
    if (isBlankOrEndMarker(username)) {
        console.showError(Messages::INVALID_USERNAME);
        return;
    }
    if (username.size() > static_cast<std::string::size_type>(Constants::MAX_USERNAME_LENGTH)) {
        console.showError(Messages::USERNAME_TOO_LONG);
        return;
    }
    // a name deleted earlier this session is gone from the registry, so it can be reused
    if (session.getAccounts().find(username) != NULL) {
        console.showError(Messages::USERNAME_ALREADY_EXISTS);
        return;
    }

    std::string accountType;
    if (!console.ask(Messages::USER_TYPE_PROMPT, accountType)) {
        return;
    }
    if (!Account::isValidType(accountType)) {
        console.showError(Messages::INVALID_USER_TYPE);
        return;
    }

    session.getAccounts().add(Account(username, accountType, 0));
    session.getLog().recordAccountLine(Constants::CREATE_CODE, username, accountType, 0);
    console.show(Messages::USER_CREATED);
}
