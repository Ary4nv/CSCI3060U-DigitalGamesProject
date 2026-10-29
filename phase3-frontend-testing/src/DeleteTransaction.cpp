#include "DeleteTransaction.h"
#include "Constants.h"
#include "Messages.h"

// Makes a delete transaction.
DeleteTransaction::DeleteTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Only admins can delete accounts.
bool DeleteTransaction::isPermittedFor(const Account& user) const {
    return user.isAdmin();
}

// Asks for the username, removes that account and records a delete (02)
// line. If the admin deleted themselves, the session ends with no
// "Logout successful." message.
void DeleteTransaction::execute() {
    std::string username;
    if (!console.ask(Messages::DELETE_USERNAME_PROMPT, username)) {
        return;
    }
    if (isBlankOrEndMarker(username)) {
        console.showError(Messages::INVALID_USERNAME);
        return;
    }
    Account* found = session.getAccounts().find(username);
    if (found == NULL) {
        console.showError(Messages::NO_SUCH_USER);
        return;
    }

    // copy the account first because the pointer is not valid after remove()
    // games the deleted user listed are left alone (team decision)
    Account deleted = *found;
    session.getAccounts().remove(username);
    session.getLog().recordAccountLine(Constants::DELETE_CODE, deleted.getUsername(),
                                       deleted.getType(), deleted.getCredit());
    console.show(Messages::USER_DELETED);

    // an admin who deleted themselves is logged out right away
    if (deleted.getUsername() == session.getCurrentUsername()) {
        if (!session.end(deleted)) {
            console.showError(Messages::CANNOT_WRITE_DAILY_FILE);
        }
    }
}
