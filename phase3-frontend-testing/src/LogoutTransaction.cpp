#include "LogoutTransaction.h"
#include "Messages.h"

// Makes a logout transaction.
LogoutTransaction::LogoutTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Ends the session with the user's final account state and prints
// "Logout successful.", or an error if the daily file can't be written.
void LogoutTransaction::execute() {
    // copy the account so the 00 line uses the credit as it is right now
    Account finalState = *session.getCurrentUser();
    if (!session.end(finalState)) {
        console.showError(Messages::CANNOT_WRITE_DAILY_FILE);
        return;
    }
    console.show(Messages::LOGOUT_SUCCESSFUL);
}
