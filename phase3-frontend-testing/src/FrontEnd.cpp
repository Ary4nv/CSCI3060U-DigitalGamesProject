#include "FrontEnd.h"
#include "Messages.h"

// Sets up the console, the session and the factory that makes transactions.
FrontEnd::FrontEnd(const FilePaths& filePaths, std::istream& input, std::ostream& output)
    : console(input, output), session(filePaths), factory(console, session) {
}

// Main loop: prints "Enter transaction:", reads a command and handles it,
// until there is no more input.
void FrontEnd::run() {
    std::string command;
    while (console.ask(Messages::TRANSACTION_PROMPT, command)) {
        handleCommand(command);
    }
}

// Handles one command. Unknown words are invalid, known ones need a login
// (except login itself), and the logged in account type must be allowed to use it.
void FrontEnd::handleCommand(const std::string& command) {
    std::unique_ptr<Transaction> transaction = factory.create(command);
    if (!transaction) {
        console.showError(Messages::INVALID_TRANSACTION);
        return;
    }

    if (transaction->requiresLogin() && !session.isLoggedIn()) {
        console.showError(Messages::PLEASE_LOGIN_FIRST);
        return;
    }
    // permission check happens here so each transaction doesn't repeat it
    if (session.isLoggedIn() && !transaction->isPermittedFor(*session.getCurrentUser())) {
        console.showError(Messages::NOT_ALLOWED_FOR_ACCOUNT_TYPE);
        return;
    }

    transaction->execute();
}
