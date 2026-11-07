#include "SearchTransaction.h"
#include <vector>
#include "FieldFormat.h"
#include "Game.h"
#include "Messages.h"

// Makes a search transaction.
SearchTransaction::SearchTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// True if this account should show up in the results for the logged in user.
// An admin with no game for sale is only shown to other admins.
bool SearchTransaction::isVisible(const Account& account) {
    if (!account.isAdmin() || session.getCurrentUser()->isAdmin()) {
        return true;
    }

    const std::vector<Game>& games = session.getGames().getAll();
    for (std::vector<Game>::size_type i = 0; i < games.size(); i++) {
        if (games[i].getSeller() == account.getUsername()) {
            return true;
        }
    }
    return false;
}

// Asks for the search text and prints the matching games and users,
// or a message saying nothing matched.
void SearchTransaction::execute() {
    std::string text;
    if (!console.ask(Messages::SEARCH_TEXT_PROMPT, text)) {
        return;
    }
    if (text.empty()) {
        console.showError(Messages::INVALID_SEARCH_TEXT);
        return;
    }

    // games are matched on the game name only, not on the seller
    std::vector<std::string> gameLines;
    const std::vector<Game>& games = session.getGames().getAll();
    for (std::vector<Game>::size_type i = 0; i < games.size(); i++) {
        if (games[i].getName().find(text) != std::string::npos) {
            gameLines.push_back(games[i].getName() + Messages::LIST_COLUMN_SEPARATOR
                                + games[i].getSeller() + Messages::LIST_COLUMN_SEPARATOR
                                + FieldFormat::moneyDisplay(games[i].getPrice()));
        }
    }

    // users are matched on the username, credit is left out
    std::vector<std::string> userLines;
    const std::vector<Account>& accounts = session.getAccounts().getAll();
    for (std::vector<Account>::size_type i = 0; i < accounts.size(); i++) {
        if (accounts[i].getUsername().find(text) != std::string::npos && isVisible(accounts[i])) {
            userLines.push_back(accounts[i].getUsername() + Messages::LIST_COLUMN_SEPARATOR
                                + accounts[i].getType());
        }
    }

    if (gameLines.empty() && userLines.empty()) {
        console.show(Messages::NO_MATCHES_FOUND);
        return;
    }
    if (!gameLines.empty()) {
        console.show(Messages::GAMES_FOUND_HEADING);
        for (std::vector<std::string>::size_type i = 0; i < gameLines.size(); i++) {
            console.show(gameLines[i]);
        }
    }
    if (!userLines.empty()) {
        console.show(Messages::USERS_FOUND_HEADING);
        for (std::vector<std::string>::size_type i = 0; i < userLines.size(); i++) {
            console.show(userLines[i]);
        }
    }
}
