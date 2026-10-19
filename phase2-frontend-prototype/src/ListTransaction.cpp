#include "ListTransaction.h"
#include <vector>
#include "FieldFormat.h"
#include "Game.h"
#include "Messages.h"

// Makes a list transaction.
ListTransaction::ListTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Prints a heading and one "name | seller | price" line per game,
// or a message saying no games are for sale.
void ListTransaction::execute() {
    const std::vector<Game>& games = session.getGames().getAll();
    if (games.empty()) {
        console.show(Messages::NO_GAMES_FOR_SALE);
        return;
    }

    console.show(Messages::GAMES_FOR_SALE_HEADING);
    for (std::vector<Game>::size_type i = 0; i < games.size(); i++) {
        console.show(games[i].getName() + Messages::LIST_COLUMN_SEPARATOR
                     + games[i].getSeller() + Messages::LIST_COLUMN_SEPARATOR
                     + FieldFormat::moneyDisplay(games[i].getPrice()));
    }
}
