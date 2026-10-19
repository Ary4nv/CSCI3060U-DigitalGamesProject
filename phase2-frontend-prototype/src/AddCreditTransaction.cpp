#include "AddCreditTransaction.h"
#include "Constants.h"
#include "Messages.h"

// Makes an addcredit transaction.
AddCreditTransaction::AddCreditTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Admins are asked which account gets the credit, everyone else only adds to
// their own. Returns NULL if the admin's answer is not an existing user (error already shown).
Account* AddCreditTransaction::askForTargetAccount() {
    Account* currentUser = session.getCurrentUser();
    if (!currentUser->isAdmin()) {
        return currentUser;
    }
    return askForExistingAccount(Messages::USERNAME_PROMPT);
}

// Checks the account wouldn't go over the maximum credit or over the session
// limit. Shows an error and returns false if it would.
bool AddCreditTransaction::amountIsAllowed(const Account& target, Cents amount) {
    if (!target.canReceive(amount)) {
        console.showError(Messages::CREDIT_LIMIT_EXCEEDED);
        return false;
    }
    // limit is per account for the whole session, not per transaction
    Cents alreadyAdded = session.getCreditAddedThisSession(target.getUsername());
    if (alreadyAdded + amount > Constants::SESSION_CREDIT_LIMIT) {
        console.showError(Messages::SESSION_CREDIT_LIMIT_EXCEEDED);
        return false;
    }
    return true;
}

// Asks for the amount (and the username for admins), checks the limits, adds the
// credit and records an addcredit (06) line with the amount that was added.
void AddCreditTransaction::execute() {
    Cents amount = 0;
    if (!askForPositiveAmount(amount)) {
        return;
    }
    Account* target = askForTargetAccount();
    if (target == NULL || !amountIsAllowed(*target, amount)) {
        return;
    }

    target->addCredit(amount);
    session.rememberCreditAdded(target->getUsername(), amount);
    // the 06 line holds the amount added, not the new total
    session.getLog().recordAccountLine(Constants::ADD_CREDIT_CODE, target->getUsername(),
                                       target->getType(), amount);
    console.show(Messages::CREDIT_ADDED);
}
