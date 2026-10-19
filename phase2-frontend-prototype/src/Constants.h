#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// Cents
// Every amount of money in the Front End (credit, prices, refunds) is stored
// as a whole number of cents, so 15.50 is stored as 1550. Using a whole number
// instead of a double keeps all money arithmetic exact.
typedef long long Cents;

// Constants
// Every limit, field width, keyword and transaction code used by the Front
// End, kept in one place so no value is typed twice. This is a namespace, not
// a class: it only holds values and is never instantiated.
namespace Constants
{
    // ----- Field lengths (in characters) -----

    // Longest allowed username; also the width of a username field in files.
    const int MAX_USERNAME_LENGTH = 15;

    // Longest allowed game name; also the width of a game name field in files.
    const int MAX_GAME_NAME_LENGTH = 25;

    // Width of an account type field, such as AA.
    const int ACCOUNT_TYPE_LENGTH = 2;

    // Width of a credit field in files, such as 000500.00.
    const int CREDIT_FIELD_WIDTH = 9;

    // Width of a price field in files, such as 015.00.
    const int PRICE_FIELD_WIDTH = 6;

    // Width of the transaction code at the start of a daily file line, such as 01.
    const int TRANSACTION_CODE_LENGTH = 2;

    // Full length of one user accounts file line: username, type, credit.
    const int ACCOUNT_LINE_LENGTH =
        MAX_USERNAME_LENGTH + 1 + ACCOUNT_TYPE_LENGTH + 1 + CREDIT_FIELD_WIDTH;

    // Full length of one available games file line: name, seller, price.
    const int GAME_LINE_LENGTH =
        MAX_GAME_NAME_LENGTH + 1 + MAX_USERNAME_LENGTH + 1 + PRICE_FIELD_WIDTH;

    // ----- Money limits (in cents) -----

    // Number of cents in one dollar.
    const Cents CENTS_PER_DOLLAR = 100;

    // Highest credit any account may hold: 999999.99.
    const Cents MAX_CREDIT = 99999999;

    // Highest price a game may be sold for: 999.99.
    const Cents MAX_PRICE = 99999;

    // Most credit that may be added to one account in one session: 1000.00.
    const Cents SESSION_CREDIT_LIMIT = 100000;

    // ----- File markers -----

    // Text that marks the last line of an input file. It can't be used as a name.
    const std::string END_MARKER = "END";

    // Character used to fill and separate fixed width file fields.
    const char FIELD_SEPARATOR = ' ';

    // ----- Account types -----

    const std::string ADMIN_TYPE = "AA";
    const std::string FULL_STANDARD_TYPE = "FS";
    const std::string BUY_STANDARD_TYPE = "BS";
    const std::string SELL_STANDARD_TYPE = "SS";

    // ----- Daily transaction file codes -----

    const std::string LOGOUT_CODE = "00";
    const std::string CREATE_CODE = "01";
    const std::string DELETE_CODE = "02";
    const std::string SELL_CODE = "03";
    const std::string BUY_CODE = "04";
    const std::string REFUND_CODE = "05";
    const std::string ADD_CREDIT_CODE = "06";

    // ----- Command words typed at the "Enter transaction:" prompt -----

    const std::string LOGIN_COMMAND = "login";
    const std::string LOGOUT_COMMAND = "logout";
    const std::string CREATE_COMMAND = "create";
    const std::string DELETE_COMMAND = "delete";
    const std::string SELL_COMMAND = "sell";
    const std::string BUY_COMMAND = "buy";
    const std::string REFUND_COMMAND = "refund";
    const std::string ADD_CREDIT_COMMAND = "addcredit";
    const std::string LIST_COMMAND = "list";
    const std::string LIST_ACCOUNTS_COMMAND = "listaccounts";
}

#endif
