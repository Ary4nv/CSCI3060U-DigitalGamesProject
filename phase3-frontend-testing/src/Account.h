#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Constants.h"

// Account
// One user account: its username, its account type (AA, FS, BS or SS) and its
// credit in cents. It also knows what its type is allowed to do (buy, sell,
// admin transactions) and keeps its credit under the maximum.
class Account
{
public:
    // Account
    // Makes an empty account (no username, no type, 0 credit) so that
    // parseFileLine has an account to fill in.
    Account();

    // Account
    // Makes an account with the given username, account type and credit in cents.
    Account(const std::string& username, const std::string& accountType, Cents credit);

    // isValidType
    // True if accountType is one of AA, FS, BS or SS.
    static bool isValidType(const std::string& accountType);

    // parseFileLine
    // Reads one 28 character user accounts file line ("username type credit")
    // into account. Returns false, leaving account unchanged, if the line is
    // the wrong length, is missing a separating space, has a blank username,
    // an invalid type, or a badly formatted credit field.
    static bool parseFileLine(const std::string& line, Account& account);

    // getUsername
    // Returns the username.
    std::string getUsername() const;

    // getType
    // Returns the account type, such as AA.
    std::string getType() const;

    // getCredit
    // Returns the credit in cents.
    Cents getCredit() const;

    // isAdmin
    // True if this is an admin (AA) account.
    bool isAdmin() const;

    // canBuy
    // True unless this is a sell-standard (SS) account.
    bool canBuy() const;

    // canSell
    // True unless this is a buy-standard (BS) account.
    bool canSell() const;

    // canReceive
    // True if adding amount cents keeps the credit at or under 999,999.99.
    bool canReceive(Cents amount) const;

    // addCredit
    // Adds amount cents to the credit. The caller checks canReceive first.
    void addCredit(Cents amount);

    // removeCredit
    // Takes amount cents away from the credit. The caller checks there is enough first.
    void removeCredit(Cents amount);

private:
    // The account's username, with no trailing spaces.
    std::string username;

    // The account's type: AA, FS, BS or SS.
    std::string accountType;

    // The account's credit in cents.
    Cents credit;
};

#endif
