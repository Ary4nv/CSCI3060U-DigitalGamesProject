#include "Account.h"

#include "FieldFormat.h"

// Where each field starts in a user accounts file line:
// username (15), space, type (2), space, credit (9).
static const int TYPE_START = Constants::MAX_USERNAME_LENGTH + 1;
static const int CREDIT_START = TYPE_START + Constants::ACCOUNT_TYPE_LENGTH + 1;

// Account
// Makes an empty account for parseFileLine to fill in.
Account::Account()
    : username(""), accountType(""), credit(0)
{
}

// Account
// Makes an account with these values.
Account::Account(const std::string& username, const std::string& accountType, Cents credit)
    : username(username), accountType(accountType), credit(credit)
{
}

// isValidType
// True for AA, FS, BS or SS.
bool Account::isValidType(const std::string& accountType)
{
    return accountType == Constants::ADMIN_TYPE
           || accountType == Constants::FULL_STANDARD_TYPE
           || accountType == Constants::BUY_STANDARD_TYPE
           || accountType == Constants::SELL_STANDARD_TYPE;
}

// parseFileLine
// Splits a 28 character line into its three fields and checks each one.
bool Account::parseFileLine(const std::string& line, Account& account)
{
    if (static_cast<int>(line.size()) != Constants::ACCOUNT_LINE_LENGTH)
    {
        return false;
    }

    bool separatorsArePresent = line[TYPE_START - 1] == Constants::FIELD_SEPARATOR
                                && line[CREDIT_START - 1] == Constants::FIELD_SEPARATOR;
    if (!separatorsArePresent)
    {
        return false;
    }

    std::string username = FieldFormat::trimRight(line.substr(0, Constants::MAX_USERNAME_LENGTH));
    std::string accountType = line.substr(TYPE_START, Constants::ACCOUNT_TYPE_LENGTH);
    std::string creditField = line.substr(CREDIT_START, Constants::CREDIT_FIELD_WIDTH);

    Cents credit = 0;
    bool fieldsAreValid = !username.empty()
                          && isValidType(accountType)
                          && FieldFormat::parseMoneyField(creditField, credit);
    if (!fieldsAreValid)
    {
        return false;
    }

    account = Account(username, accountType, credit);
    return true;
}

// getUsername
// Returns the username.
std::string Account::getUsername() const
{
    return username;
}

// getType
// Returns the account type.
std::string Account::getType() const
{
    return accountType;
}

// getCredit
// Returns the credit in cents.
Cents Account::getCredit() const
{
    return credit;
}

// isAdmin
// True for AA accounts.
bool Account::isAdmin() const
{
    return accountType == Constants::ADMIN_TYPE;
}

// canBuy
// True unless the account is sell-standard (SS).
bool Account::canBuy() const
{
    return accountType != Constants::SELL_STANDARD_TYPE;
}

// canSell
// True unless the account is buy-standard (BS).
bool Account::canSell() const
{
    return accountType != Constants::BUY_STANDARD_TYPE;
}

// canReceive
// True if the credit stays at or under the maximum after adding amount.
bool Account::canReceive(Cents amount) const
{
    return credit + amount <= Constants::MAX_CREDIT;
}

// addCredit
// Adds amount to the credit.
void Account::addCredit(Cents amount)
{
    credit += amount;
}

// removeCredit
// Takes amount away from the credit.
void Account::removeCredit(Cents amount)
{
    credit -= amount;
}
