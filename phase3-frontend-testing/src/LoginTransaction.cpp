#include "LoginTransaction.h"
#include "Messages.h"

// Makes a login transaction.
LoginTransaction::LoginTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Login can be used when nobody is logged in yet.
bool LoginTransaction::requiresLogin() const {
    return false;
}

// Loads the accounts file into the session. Shows the right error and
// returns false if the file is missing or not in the correct format.
bool LoginTransaction::loadAccountsFile() {
    FileLoadStatus status = session.getAccounts().loadFromFile(session.getFilePaths().accountsFile);
    if (status == FILE_CANNOT_OPEN) {
        console.showError(Messages::CANNOT_OPEN_ACCOUNTS_FILE);
    } else if (status == FILE_BAD_FORMAT) {
        console.showError(Messages::BAD_ACCOUNTS_FILE_FORMAT);
    }
    return status == FILE_LOADED;
}

// Loads the games file into the session. Shows the right error and
// returns false if the file is missing or not in the correct format.
bool LoginTransaction::loadGamesFile() {
    FileLoadStatus status = session.getGames().loadFromFile(session.getFilePaths().gamesFile);
    if (status == FILE_CANNOT_OPEN) {
        console.showError(Messages::CANNOT_OPEN_GAMES_FILE);
    } else if (status == FILE_BAD_FORMAT) {
        console.showError(Messages::BAD_GAMES_FILE_FORMAT);
    }
    return status == FILE_LOADED;
}

// Logs a user in: refuses if someone is already logged in, loads the accounts
// file, asks for the username, checks it exists, loads the games file and starts the session.
void LoginTransaction::execute() {
    if (session.isLoggedIn()) {
        console.showError(Messages::ALREADY_LOGGED_IN);
        return;
    }
    // accounts file is loaded before asking for the username
    if (!loadAccountsFile()) {
        return;
    }

    std::string username;
    if (!console.ask(Messages::USERNAME_PROMPT, username)) {
        return;
    }
    if (isBlankOrEndMarker(username)) {
        console.showError(Messages::INVALID_USERNAME);
        return;
    }
    if (session.getAccounts().find(username) == NULL) {
        console.showError(Messages::NO_SUCH_USER);
        return;
    }
    // games file only gets loaded once the username is ok
    if (!loadGamesFile()) {
        return;
    }

    session.begin(username);
    console.show(Messages::LOGIN_SUCCESSFUL);
}
