#include "TransactionFactory.h"
#include "AddCreditTransaction.h"
#include "BuyTransaction.h"
#include "Constants.h"
#include "CreateTransaction.h"
#include "DeleteTransaction.h"
#include "ListAccountsTransaction.h"
#include "ListTransaction.h"
#include "LoginTransaction.h"
#include "LogoutTransaction.h"
#include "RefundTransaction.h"
#include "SellTransaction.h"

// Keeps the console and session to hand to each transaction it makes.
TransactionFactory::TransactionFactory(Console& newConsole, Session& newSession)
    : console(newConsole), session(newSession) {
}

// Makes the transaction for this command word (case sensitive).
// Returns an empty pointer if the word is not a transaction.
std::unique_ptr<Transaction> TransactionFactory::create(const std::string& command) {
    if (command == Constants::LOGIN_COMMAND) {
        return std::unique_ptr<Transaction>(new LoginTransaction(console, session));
    }
    if (command == Constants::LOGOUT_COMMAND) {
        return std::unique_ptr<Transaction>(new LogoutTransaction(console, session));
    }
    if (command == Constants::CREATE_COMMAND) {
        return std::unique_ptr<Transaction>(new CreateTransaction(console, session));
    }
    if (command == Constants::DELETE_COMMAND) {
        return std::unique_ptr<Transaction>(new DeleteTransaction(console, session));
    }
    if (command == Constants::SELL_COMMAND) {
        return std::unique_ptr<Transaction>(new SellTransaction(console, session));
    }
    if (command == Constants::BUY_COMMAND) {
        return std::unique_ptr<Transaction>(new BuyTransaction(console, session));
    }
    if (command == Constants::REFUND_COMMAND) {
        return std::unique_ptr<Transaction>(new RefundTransaction(console, session));
    }
    if (command == Constants::ADD_CREDIT_COMMAND) {
        return std::unique_ptr<Transaction>(new AddCreditTransaction(console, session));
    }
    if (command == Constants::LIST_COMMAND) {
        return std::unique_ptr<Transaction>(new ListTransaction(console, session));
    }
    if (command == Constants::LIST_ACCOUNTS_COMMAND) {
        return std::unique_ptr<Transaction>(new ListAccountsTransaction(console, session));
    }
    return std::unique_ptr<Transaction>();
}
