#include "Transaction.h"
#include "Constants.h"
#include "FieldFormat.h"
#include "Messages.h"

// Keeps the console and session so the transaction can use them.
Transaction::Transaction(Console& newConsole, Session& newSession)
    : console(newConsole), session(newSession) {
}

// Needed so a transaction can be deleted through a Transaction pointer.
Transaction::~Transaction() {
}

// Most transactions need someone to be logged in. Login overrides this.
bool Transaction::requiresLogin() const {
    return true;
}

// Most transactions are allowed for every account type. The restricted ones override this.
bool Transaction::isPermittedFor(const Account&) const {
    return true;
}

// True if the typed text is empty or is the END marker, neither can be a name.
bool Transaction::isBlankOrEndMarker(const std::string& text) {
    return text.empty() || text == Constants::END_MARKER;
}

// Shows the prompt, reads a username and looks it up.
// Returns the account, or NULL if the input ended or there is no such user (error already shown).
Account* Transaction::askForExistingAccount(const std::string& prompt) {
    std::string username;
    if (!console.ask(prompt, username)) {
        return NULL;
    }

    Account* account = session.getAccounts().find(username);
    if (account == NULL) {
        console.showError(Messages::NO_SUCH_USER);
    }
    return account;
}

// Asks "Enter amount of credit:" and reads a money amount above zero.
// Returns false if the input ended or the amount is not valid (error already shown).
bool Transaction::askForPositiveAmount(Cents& amount) {
    std::string amountText;
    if (!console.ask(Messages::CREDIT_AMOUNT_PROMPT, amountText)) {
        return false;
    }

    if (!FieldFormat::parseMoney(amountText, amount) || amount <= 0) {
        console.showError(Messages::INVALID_AMOUNT);
        return false;
    }
    return true;
}
