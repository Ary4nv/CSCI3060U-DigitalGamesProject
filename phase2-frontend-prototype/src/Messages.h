#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>

// Messages
// Every prompt, confirmation and error the Front End prints, worded exactly
// as in our Phase 1 expected output files. Keeping them here means each text
// is typed once. This is a namespace, not a class: it only holds values.
//
// Error texts leave out the "ERROR: " prefix, because Console::showError adds it.
namespace Messages
{
    // ----- Prompts (printed before reading a line of input) -----

    const std::string TRANSACTION_PROMPT = "Enter transaction:";
    const std::string USERNAME_PROMPT = "Enter username:";
    const std::string NEW_USERNAME_PROMPT = "Enter new username:";
    const std::string USER_TYPE_PROMPT = "Enter user type (AA, FS, BS, SS):";
    const std::string DELETE_USERNAME_PROMPT = "Enter username to delete:";
    const std::string GAME_NAME_PROMPT = "Enter game name:";
    const std::string PRICE_PROMPT = "Enter price:";
    const std::string SELLER_USERNAME_PROMPT = "Enter seller username:";
    const std::string BUYER_USERNAME_PROMPT = "Enter buyer username:";
    const std::string CREDIT_AMOUNT_PROMPT = "Enter amount of credit:";

    // ----- Confirmations (printed when a transaction succeeds) -----

    const std::string LOGIN_SUCCESSFUL = "Login successful.";
    const std::string LOGOUT_SUCCESSFUL = "Logout successful.";
    const std::string USER_CREATED = "User created.";
    const std::string USER_DELETED = "User deleted.";
    const std::string GAME_PUT_UP_FOR_SALE = "Game put up for sale.";
    const std::string GAME_PURCHASED = "Game purchased.";
    const std::string REFUND_COMPLETE = "Refund complete.";
    const std::string CREDIT_ADDED = "Credit added.";

    // ----- List output -----

    // Heading printed before the games for sale (list).
    const std::string GAMES_FOR_SALE_HEADING = "Games for sale:";

    // Printed instead of the games when nothing is for sale (list).
    const std::string NO_GAMES_FOR_SALE = "No games are currently for sale.";

    // Heading printed before the accounts (listaccounts).
    const std::string ACTIVE_ACCOUNTS_HEADING = "Active accounts:";

    // Placed between the columns of a list row, as in "name | seller | price".
    const std::string LIST_COLUMN_SEPARATOR = " | ";

    // ----- Errors -----

    // Put in front of every error by Console::showError.
    const std::string ERROR_PREFIX = "ERROR: ";

    // Command and permission errors
    const std::string INVALID_TRANSACTION = "invalid transaction";
    const std::string PLEASE_LOGIN_FIRST = "please login first";
    const std::string NOT_ALLOWED_FOR_ACCOUNT_TYPE = "not allowed for this account type";

    // Login and input file errors
    const std::string ALREADY_LOGGED_IN = "already logged in";
    const std::string CANNOT_OPEN_ACCOUNTS_FILE = "cannot open user accounts file";
    const std::string BAD_ACCOUNTS_FILE_FORMAT = "user accounts file is not in the correct format";
    const std::string CANNOT_OPEN_GAMES_FILE = "cannot open available games file";
    const std::string BAD_GAMES_FILE_FORMAT = "available games file is not in the correct format";

    // Output file errors
    const std::string CANNOT_WRITE_DAILY_FILE = "cannot write daily transaction file";

    // Username and account errors
    const std::string INVALID_USERNAME = "invalid username";
    const std::string NO_SUCH_USER = "no such user";
    const std::string USERNAME_TOO_LONG = "username too long (max 15)";
    const std::string USERNAME_ALREADY_EXISTS = "username already exists";
    const std::string INVALID_USER_TYPE = "invalid user type";

    // Sell errors
    const std::string INVALID_GAME_NAME = "invalid game name";
    const std::string GAME_NAME_TOO_LONG = "game name too long (max 25)";
    const std::string GAME_ALREADY_FOR_SALE = "game already for sale";
    const std::string INVALID_PRICE = "invalid price";
    const std::string PRICE_TOO_HIGH = "price too high (max 999.99)";

    // Buy errors
    const std::string GAME_NOT_FOUND = "game not found";
    const std::string SELLER_DOES_NOT_MATCH = "seller does not match the listing";
    const std::string GAME_NOT_AVAILABLE_THIS_SESSION = "game not available for purchase this session";
    const std::string CANNOT_BUY_OWN_GAME = "cannot buy your own game";
    const std::string GAME_ALREADY_OWNED = "game already owned";
    const std::string SELLER_CREDIT_LIMIT_EXCEEDED = "seller credit limit exceeded";

    // Refund and addcredit errors
    const std::string BUYER_AND_SELLER_MUST_DIFFER = "buyer and seller must be different";
    const std::string INVALID_AMOUNT = "invalid amount";
    const std::string NOT_ENOUGH_CREDIT = "not enough credit";
    const std::string CREDIT_LIMIT_EXCEEDED = "credit limit exceeded";
    const std::string SESSION_CREDIT_LIMIT_EXCEEDED = "session credit limit of 1000.00 exceeded";
}

#endif
